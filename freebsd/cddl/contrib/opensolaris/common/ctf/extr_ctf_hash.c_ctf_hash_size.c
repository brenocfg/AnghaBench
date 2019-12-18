#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_3__ {scalar_t__ h_nelems; } ;
typedef  TYPE_1__ ctf_hash_t ;

/* Variables and functions */

uint_t
ctf_hash_size(const ctf_hash_t *hp)
{
	return (hp->h_nelems ? hp->h_nelems - 1 : 0);
}