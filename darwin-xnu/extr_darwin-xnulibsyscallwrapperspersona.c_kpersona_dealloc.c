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
typedef  int /*<<< orphan*/  uid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PERSONA_OP_DEALLOC ; 
 int __persona (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 

int kpersona_dealloc(uid_t id)
{
	size_t idlen = 1;
	return __persona(PERSONA_OP_DEALLOC, 0, NULL, &id, &idlen);
}