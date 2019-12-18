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
struct adb_request {int reply_len; int /*<<< orphan*/ * reply; } ;

/* Variables and functions */
 int ADBREQ_REPLY ; 
 int ADBREQ_SYNC ; 
 int /*<<< orphan*/  ADB_FLUSH (int) ; 
 int /*<<< orphan*/  ADB_READREG (int,int) ; 
 int /*<<< orphan*/  ADB_WRITEREG (int,int) ; 
 int /*<<< orphan*/  adb_request (struct adb_request*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void 
init_trackpad(int id)
{
	struct adb_request req;
	unsigned char r1_buffer[8];

	printk(" (trackpad)");

	adb_request(&req, NULL, ADBREQ_SYNC | ADBREQ_REPLY, 1,
		    ADB_READREG(id,1));
	if (req.reply_len < 8)
	    printk("bad length for reg. 1\n");
	else
	{
	    memcpy(r1_buffer, &req.reply[1], 8);

	    adb_request(&req, NULL, ADBREQ_SYNC, 9,
	        ADB_WRITEREG(id,1),
	            r1_buffer[0],
	            r1_buffer[1],
	            r1_buffer[2],
	            r1_buffer[3],
	            r1_buffer[4],
	            r1_buffer[5],
	            0x0d,
	            r1_buffer[7]);

            adb_request(&req, NULL, ADBREQ_SYNC, 9,
	        ADB_WRITEREG(id,2),
	    	    0x99,
	    	    0x94,
	    	    0x19,
	    	    0xff,
	    	    0xb2,
	    	    0x8a,
	    	    0x1b,
	    	    0x50);

	    adb_request(&req, NULL, ADBREQ_SYNC, 9,
	        ADB_WRITEREG(id,1),
	            r1_buffer[0],
	            r1_buffer[1],
	            r1_buffer[2],
	            r1_buffer[3],
	            r1_buffer[4],
	            r1_buffer[5],
	            0x03, /*r1_buffer[6],*/
	            r1_buffer[7]);

	    /* Without this flush, the trackpad may be locked up */
	    adb_request(&req, NULL, ADBREQ_SYNC, 1, ADB_FLUSH(id));
        }
}