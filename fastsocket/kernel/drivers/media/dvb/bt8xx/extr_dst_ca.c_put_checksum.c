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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DST_CA_DEBUG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int dst_check_sum (int*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static void put_checksum(u8 *check_string, int length)
{
	dprintk(verbose, DST_CA_DEBUG, 1, " Computing string checksum.");
	dprintk(verbose, DST_CA_DEBUG, 1, "  -> string length : 0x%02x", length);
	check_string[length] = dst_check_sum (check_string, length);
	dprintk(verbose, DST_CA_DEBUG, 1, "  -> checksum      : 0x%02x", check_string[length]);
}