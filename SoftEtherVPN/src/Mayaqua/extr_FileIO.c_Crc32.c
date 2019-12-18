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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Crc32Finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Crc32First (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT Crc32(void *buf, UINT pos, UINT len)
{
	return Crc32Finish(Crc32First(buf, pos, len));
}