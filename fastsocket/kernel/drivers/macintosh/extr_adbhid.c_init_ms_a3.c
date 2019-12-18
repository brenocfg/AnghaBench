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
struct adb_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADBREQ_SYNC ; 
 int /*<<< orphan*/  ADB_FLUSH (int) ; 
 int /*<<< orphan*/  ADB_WRITEREG (int,int) ; 
 int /*<<< orphan*/  adb_request (struct adb_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void
init_ms_a3(int id)
{
	struct adb_request req;

	printk(" (Mouse Systems A3 Mouse, or compatible)");
	adb_request(&req, NULL, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id, 0x2),
	    0x00,
	    0x07);
 
 	adb_request(&req, NULL, ADBREQ_SYNC, 1, ADB_FLUSH(id));
}