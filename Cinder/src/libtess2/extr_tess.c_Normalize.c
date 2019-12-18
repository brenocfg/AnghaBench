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
typedef  int TESSreal ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int sqrtf (int) ; 

__attribute__((used)) static void Normalize( TESSreal v[3] )
{
	TESSreal len = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];

	assert( len > 0 );
	len = sqrtf( len );
	v[0] /= len;
	v[1] /= len;
	v[2] /= len;
}