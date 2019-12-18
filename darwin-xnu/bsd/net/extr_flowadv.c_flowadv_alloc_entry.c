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
struct flowadv_fcentry {int dummy; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct flowadv_fcentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fadv_zone ; 
 int /*<<< orphan*/  fadv_zone_size ; 
 struct flowadv_fcentry* zalloc (int /*<<< orphan*/ ) ; 
 struct flowadv_fcentry* zalloc_noblock (int /*<<< orphan*/ ) ; 

struct flowadv_fcentry *
flowadv_alloc_entry(int how)
{
	struct flowadv_fcentry *fce;

	fce = (how == M_WAITOK) ? zalloc(fadv_zone) : zalloc_noblock(fadv_zone);
	if (fce != NULL)
		bzero(fce, fadv_zone_size);

	return (fce);
}