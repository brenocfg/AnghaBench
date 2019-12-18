#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  registers ;

/* Variables and functions */
 int R0 ; 
 int SUCCESS ; 
 int USP ; 
 int /*<<< orphan*/  copy_registers (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* current_thread_c ; 
 void* current_thread_g ; 
 void* executing_task ; 
 int /*<<< orphan*/  gdb_cris_strcpy (char*,char*) ; 
 scalar_t__ gdb_cris_strlen (char*) ; 
 char hex_asc_hi (void*) ; 
 char hex_asc_lo (void*) ; 
 char* mem2hex (char*,unsigned char*,int /*<<< orphan*/ ) ; 
 char* pack_hex_byte (char*,int) ; 
 size_t pos ; 
 int /*<<< orphan*/  putpacket (char*) ; 
 int read_register (int,unsigned int*) ; 
 int /*<<< orphan*/  reg ; 
 int /*<<< orphan*/  reg_g ; 
 int /*<<< orphan*/ * register_size ; 
 char* remcomOutBuffer ; 

__attribute__((used)) static void
stub_is_stopped(int sigval)
{
	char *ptr = remcomOutBuffer;
	int regno;

	unsigned int reg_cont;
	int status;
        
	/* Send trap type (converted to signal) */

	*ptr++ = 'T';
	ptr = pack_hex_byte(ptr, sigval);

	/* Send register contents. We probably only need to send the
	 * PC, frame pointer and stack pointer here. Other registers will be
	 * explicitly asked for. But for now, send all.
	 */
	
	for (regno = R0; regno <= USP; regno++) {
		/* Store n...:r...; for the registers in the buffer. */

                status = read_register (regno, &reg_cont);
                
		if (status == SUCCESS) {
			ptr = pack_hex_byte(ptr, regno);
                        *ptr++ = ':';

                        ptr = mem2hex(ptr, (unsigned char *)&reg_cont,
                                      register_size[regno]);
                        *ptr++ = ';';
                }
                
	}

#ifdef PROCESS_SUPPORT
	/* Store the registers of the executing thread. Assume that both step,
	   continue, and register content requests are with respect to this
	   thread. The executing task is from the operating system scheduler. */

	current_thread_c = executing_task;
	current_thread_g = executing_task;

	/* A struct assignment translates into a libc memcpy call. Avoid
	   all libc functions in order to prevent recursive break points. */
	copy_registers (&reg_g, &reg, sizeof(registers));

	/* Store thread:r...; with the executing task TID. */
	gdb_cris_strcpy (&remcomOutBuffer[pos], "thread:");
	pos += gdb_cris_strlen ("thread:");
	remcomOutBuffer[pos++] = hex_asc_hi(executing_task);
	remcomOutBuffer[pos++] = hex_asc_lo(executing_task);
	gdb_cris_strcpy (&remcomOutBuffer[pos], ";");
#endif

	/* null-terminate and send it off */

	*ptr = 0;

	putpacket (remcomOutBuffer);
}