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
typedef  int /*<<< orphan*/  u8 ;
struct param {int is_present; int /*<<< orphan*/  word; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_be16 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const u8 *save16bit(struct param *p, const u8 *datap)
{
	p->is_present = 1;
	p->word = get_unaligned_be16(datap);
	return datap + sizeof(p->word);
}