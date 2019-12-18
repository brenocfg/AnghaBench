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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {char* str; int /*<<< orphan*/  num; } ;
struct parse_events__term {int type_val; int type_term; char* config; TYPE_1__ val; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  PARSE_EVENTS__TERM_TYPE_NUM 129 
#define  PARSE_EVENTS__TERM_TYPE_STR 128 
 struct parse_events__term* zalloc (int) ; 

__attribute__((used)) static int new_term(struct parse_events__term **_term, int type_val,
		    int type_term, char *config,
		    char *str, u64 num)
{
	struct parse_events__term *term;

	term = zalloc(sizeof(*term));
	if (!term)
		return -ENOMEM;

	INIT_LIST_HEAD(&term->list);
	term->type_val  = type_val;
	term->type_term = type_term;
	term->config = config;

	switch (type_val) {
	case PARSE_EVENTS__TERM_TYPE_NUM:
		term->val.num = num;
		break;
	case PARSE_EVENTS__TERM_TYPE_STR:
		term->val.str = str;
		break;
	default:
		return -EINVAL;
	}

	*_term = term;
	return 0;
}