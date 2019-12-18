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
struct user_regs_struct {int dummy; } ;
struct user_fpxregs_struct {int dummy; } ;
struct user_fpregs_struct {int dummy; } ;

/* Variables and functions */
 int CS ; 
 int /*<<< orphan*/  DEFINE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DEFINE_LONGS (int /*<<< orphan*/ ,int) ; 
 int DS ; 
 int EAX ; 
 int EBP ; 
 int EBX ; 
 int ECX ; 
 int EDI ; 
 int EDX ; 
 int EFL ; 
 int EIP ; 
 int ES ; 
 int ESI ; 
 int FS ; 
 int GS ; 
 int /*<<< orphan*/  HOST_CS ; 
 int /*<<< orphan*/  HOST_DS ; 
 int /*<<< orphan*/  HOST_EAX ; 
 int /*<<< orphan*/  HOST_EBP ; 
 int /*<<< orphan*/  HOST_EBX ; 
 int /*<<< orphan*/  HOST_ECX ; 
 int /*<<< orphan*/  HOST_EDI ; 
 int /*<<< orphan*/  HOST_EDX ; 
 int /*<<< orphan*/  HOST_EFLAGS ; 
 int /*<<< orphan*/  HOST_ES ; 
 int /*<<< orphan*/  HOST_ESI ; 
 int /*<<< orphan*/  HOST_FPX_SIZE ; 
 int /*<<< orphan*/  HOST_FP_SIZE ; 
 int /*<<< orphan*/  HOST_FS ; 
 int /*<<< orphan*/  HOST_GS ; 
 int /*<<< orphan*/  HOST_IP ; 
 int /*<<< orphan*/  HOST_SC_CR2 ; 
 int /*<<< orphan*/  HOST_SC_ERR ; 
 int /*<<< orphan*/  HOST_SC_TRAPNO ; 
 int /*<<< orphan*/  HOST_SP ; 
 int /*<<< orphan*/  HOST_SS ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLPRI ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int SS ; 
 int UESP ; 
 int /*<<< orphan*/  UM_FRAME_SIZE ; 
 int /*<<< orphan*/  UM_POLLIN ; 
 int /*<<< orphan*/  UM_POLLOUT ; 
 int /*<<< orphan*/  UM_POLLPRI ; 
 int /*<<< orphan*/  UM_PROT_EXEC ; 
 int /*<<< orphan*/  UM_PROT_READ ; 
 int /*<<< orphan*/  UM_PROT_WRITE ; 
 int /*<<< orphan*/  cr2 ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  sigcontext ; 
 int /*<<< orphan*/  trapno ; 

void foo(void)
{
	OFFSET(HOST_SC_TRAPNO, sigcontext, trapno);
	OFFSET(HOST_SC_ERR, sigcontext, err);
	OFFSET(HOST_SC_CR2, sigcontext, cr2);

	DEFINE_LONGS(HOST_FP_SIZE, sizeof(struct user_fpregs_struct));
	DEFINE_LONGS(HOST_FPX_SIZE, sizeof(struct user_fpxregs_struct));

	DEFINE(HOST_IP, EIP);
	DEFINE(HOST_SP, UESP);
	DEFINE(HOST_EFLAGS, EFL);
	DEFINE(HOST_EAX, EAX);
	DEFINE(HOST_EBX, EBX);
	DEFINE(HOST_ECX, ECX);
	DEFINE(HOST_EDX, EDX);
	DEFINE(HOST_ESI, ESI);
	DEFINE(HOST_EDI, EDI);
	DEFINE(HOST_EBP, EBP);
	DEFINE(HOST_CS, CS);
	DEFINE(HOST_SS, SS);
	DEFINE(HOST_DS, DS);
	DEFINE(HOST_FS, FS);
	DEFINE(HOST_ES, ES);
	DEFINE(HOST_GS, GS);
	DEFINE(UM_FRAME_SIZE, sizeof(struct user_regs_struct));

	/* XXX Duplicated between i386 and x86_64 */
	DEFINE(UM_POLLIN, POLLIN);
	DEFINE(UM_POLLPRI, POLLPRI);
	DEFINE(UM_POLLOUT, POLLOUT);

	DEFINE(UM_PROT_READ, PROT_READ);
	DEFINE(UM_PROT_WRITE, PROT_WRITE);
	DEFINE(UM_PROT_EXEC, PROT_EXEC);
}