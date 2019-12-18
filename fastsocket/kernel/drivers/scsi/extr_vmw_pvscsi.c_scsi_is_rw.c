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

/* Variables and functions */
 unsigned char READ_10 ; 
 unsigned char READ_12 ; 
 unsigned char READ_16 ; 
 unsigned char READ_6 ; 
 unsigned char WRITE_10 ; 
 unsigned char WRITE_12 ; 
 unsigned char WRITE_16 ; 
 unsigned char WRITE_6 ; 

__attribute__((used)) static int scsi_is_rw(unsigned char op)
{
	return op == READ_6  || op == WRITE_6 ||
	       op == READ_10 || op == WRITE_10 ||
	       op == READ_12 || op == WRITE_12 ||
	       op == READ_16 || op == WRITE_16;
}