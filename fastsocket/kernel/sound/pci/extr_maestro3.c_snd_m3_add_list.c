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
typedef  int /*<<< orphan*/  u16 ;
struct snd_m3 {int dummy; } ;
struct m3_list {scalar_t__ curlen; scalar_t__ mem_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMTYPE_INTERNAL_DATA ; 
 int /*<<< orphan*/  snd_m3_assp_write (struct snd_m3*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_m3_add_list(struct snd_m3 *chip, struct m3_list *list, u16 val)
{
	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  list->mem_addr + list->curlen,
			  val);
	return list->curlen++;
}