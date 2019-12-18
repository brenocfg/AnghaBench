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
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int /*<<< orphan*/  bswap32 (unsigned int) ; 
 int /*<<< orphan*/  f ; 
 int /*<<< orphan*/  fwrite (unsigned int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write32(unsigned int a)
{
	bswap32(a);
	fwrite(&a,     1, sizeof(a),  f);
}