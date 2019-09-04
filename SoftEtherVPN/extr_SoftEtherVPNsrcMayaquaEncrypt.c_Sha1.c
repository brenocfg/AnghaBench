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
 int /*<<< orphan*/  SHA1_160 ; 
 int /*<<< orphan*/  Sha (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ) ; 

void Sha1(void *dst, void *src, UINT size)
{
	Sha(SHA1_160, dst, src, size);
}