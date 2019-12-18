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
struct message {struct message* next; } ;
typedef  int /*<<< orphan*/  bf ;

/* Variables and functions */
 char* escape (char const*,char*,int) ; 
 struct message* mesage__find (char*) ; 
 int message__add_file_line (struct message*,char const*,int) ; 
 struct message* message__list ; 
 struct message* message__new (char*,char*,char const*,int) ; 

__attribute__((used)) static int message__add(const char *msg, char *option, const char *file,
			int lineno)
{
	int rc = 0;
	char bf[16384];
	char *escaped = escape(msg, bf, sizeof(bf));
	struct message *m = mesage__find(escaped);

	if (m != NULL)
		rc = message__add_file_line(m, file, lineno);
	else {
		m = message__new(escaped, option, file, lineno);

		if (m != NULL) {
			m->next	      = message__list;
			message__list = m;
		} else
			rc = -1;
	}
	return rc;
}