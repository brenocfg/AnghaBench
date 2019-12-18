#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union viosrp_iu {int dummy; } viosrp_iu ;
struct iu_entry {TYPE_1__* sbuf; } ;
struct TYPE_2__ {scalar_t__ buf; } ;

/* Variables and functions */

__attribute__((used)) static inline union viosrp_iu *vio_iu(struct iu_entry *iue)
{
	return (union viosrp_iu *) (iue->sbuf->buf);
}