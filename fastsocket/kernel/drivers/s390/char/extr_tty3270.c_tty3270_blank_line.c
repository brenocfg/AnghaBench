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
struct tty3270 {scalar_t__ nr_up; int /*<<< orphan*/  nr_lines; int /*<<< orphan*/  lines; } ;
struct string {int len; int /*<<< orphan*/  list; int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  blueprint ;

/* Variables and functions */
#define  TAC_RESET 134 
#define  TAT_COLOR 133 
#define  TAT_EXTHI 132 
#define  TAX_RESET 131 
#define  TO_RA 130 
#define  TO_SA 129 
#define  TO_SBA 128 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 struct string* tty3270_alloc_string (struct tty3270*,int) ; 

__attribute__((used)) static void
tty3270_blank_line(struct tty3270 *tp)
{
	static const unsigned char blueprint[] =
		{ TO_SBA, 0, 0, TO_SA, TAT_EXTHI, TAX_RESET,
		  TO_SA, TAT_COLOR, TAC_RESET, TO_RA, 0, 0, 0 };
	struct string *s;

	s = tty3270_alloc_string(tp, sizeof(blueprint));
	memcpy(s->string, blueprint, sizeof(blueprint));
	s->len = sizeof(blueprint);
	list_add_tail(&s->list, &tp->lines);
	tp->nr_lines++;
	if (tp->nr_up != 0)
		tp->nr_up++;
}