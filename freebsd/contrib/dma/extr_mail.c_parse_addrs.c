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
struct queue {int dummy; } ;
struct parse_state {int state; int pos; int esc; int quote; int brackets; char* addr; scalar_t__ comment; } ;

/* Variables and functions */
#define  EOL 132 
 int /*<<< orphan*/  EXPAND_WILDCARD ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
#define  MAIN 131 
#define  NONE 130 
#define  QUIT 129 
#define  START 128 
 scalar_t__ add_recp (struct queue*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct parse_state*,int) ; 
 int /*<<< orphan*/  errlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errlogx (int /*<<< orphan*/ ,char*,char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static int
parse_addrs(struct parse_state *ps, char *s, struct queue *queue)
{
	char *addr;

again:
	switch (ps->state) {
	case NONE:
		return (-1);

	case START:
		/* init our data */
		bzero(ps, sizeof(*ps));

		/* skip over header name */
		while (*s != ':')
			s++;
		s++;
		ps->state = MAIN;
		break;

	case MAIN:
		/* all fine */
		break;

	case EOL:
		switch (*s) {
		case ' ':
		case '\t':
			s++;
			/* continue */
			break;

		default:
			ps->state = QUIT;
			if (ps->pos != 0)
				goto newaddr;
			return (0);
		}

	case QUIT:
		return (0);
	}

	for (; *s != 0; s++) {
		if (ps->esc) {
			ps->esc = 0;

			switch (*s) {
			case '\r':
			case '\n':
				goto err;

			default:
				goto copy;
			}
		}

		if (ps->quote) {
			switch (*s) {
			case '"':
				ps->quote = 0;
				goto copy;

			case '\\':
				ps->esc = 1;
				goto copy;

			case '\r':
			case '\n':
				goto eol;

			default:
				goto copy;
			}
		}

		switch (*s) {
		case '(':
			ps->comment++;
			break;

		case ')':
			if (ps->comment)
				ps->comment--;
			else
				goto err;
			goto skip;

		case '"':
			ps->quote = 1;
			goto copy;

		case '\\':
			ps->esc = 1;
			goto copy;

		case '\r':
		case '\n':
			goto eol;
		}

		if (ps->comment)
			goto skip;

		switch (*s) {
		case ' ':
		case '\t':
			/* ignore whitespace */
			goto skip;

		case '<':
			/* this is the real address now */
			ps->brackets = 1;
			ps->pos = 0;
			goto skip;

		case '>':
			if (!ps->brackets)
				goto err;
			ps->brackets = 0;

			s++;
			goto newaddr;

		case ':':
			/* group - ignore */
			ps->pos = 0;
			goto skip;

		case ',':
		case ';':
			/*
			 * Next address, copy previous one.
			 * However, we might be directly after
			 * a <address>, or have two consecutive
			 * commas.
			 * Skip the comma unless there is
			 * really something to copy.
			 */
			if (ps->pos == 0)
				goto skip;
			s++;
			goto newaddr;

		default:
			goto copy;
		}

copy:
		if (ps->comment)
			goto skip;

		if (ps->pos + 1 == sizeof(ps->addr))
			goto err;
		ps->addr[ps->pos++] = *s;

skip:
		;
	}

eol:
	ps->state = EOL;
	return (0);

err:
	ps->state = QUIT;
	return (-1);

newaddr:
	ps->addr[ps->pos] = 0;
	ps->pos = 0;
	addr = strdup(ps->addr);
	if (addr == NULL)
		errlog(EX_SOFTWARE, "strdup");

	if (add_recp(queue, addr, EXPAND_WILDCARD) != 0)
		errlogx(EX_DATAERR, "invalid recipient `%s'", addr);

	goto again;
}