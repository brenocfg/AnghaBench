#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uchar ;
struct TYPE_11__ {size_t max; TYPE_2__* lp; TYPE_2__* bp; } ;
typedef  TYPE_1__ Tokenrow ;
struct TYPE_12__ {int* t; int wslen; int len; int /*<<< orphan*/  type; scalar_t__ flag; scalar_t__ hideset; } ;
typedef  TYPE_2__ Token ;
struct TYPE_13__ {int* inp; int* inl; int* inb; int fd; scalar_t__ lineinc; } ;
typedef  TYPE_3__ Source ;

/* Variables and functions */
 int COM2 ; 
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  GETACT (int) ; 
 int INS ; 
 int /*<<< orphan*/  NAME ; 
 int /*<<< orphan*/  NL ; 
 int QBSBIT ; 
 int START ; 
#define  S_COMMENT 139 
#define  S_COMNL 138 
#define  S_EOB 137 
#define  S_EOF 136 
#define  S_EOFCOM 135 
#define  S_EOFSTR 134 
#define  S_NAME 133 
#define  S_NL 132 
#define  S_SELF 131 
#define  S_SELFB 130 
#define  S_STNL 129 
#define  S_WS 128 
 int /*<<< orphan*/  UNCLASS ; 
 int /*<<< orphan*/  WARNING ; 
 int** bigfsm ; 
 TYPE_3__* cursource ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fillbuf (TYPE_3__*) ; 
 int /*<<< orphan*/  foldline (TYPE_3__*) ; 
 TYPE_2__* growtokenrow (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int quicklook (int,int) ; 
 int /*<<< orphan*/  trigraph (TYPE_3__*) ; 

int
gettokens(Tokenrow *trp, int reset)
{
	register int c, state, oldstate;
	register uchar *ip;
	register Token *tp, *maxp;
	int runelen;
	Source *s = cursource;
	int nmac = 0;
	extern char outbuf[];

	tp = trp->lp;
	ip = s->inp;
	if (reset) {
		s->lineinc = 0;
		if (ip>=s->inl) {		/* nothing in buffer */
			s->inl = s->inb;
			fillbuf(s);
			ip = s->inp = s->inb;
		} else if (ip >= s->inb+(3*INS/4)) {
			memmove(s->inb, ip, 4+s->inl-ip);
			s->inl = s->inb+(s->inl-ip);
			ip = s->inp = s->inb;
		}
	}
	maxp = &trp->bp[trp->max];
	runelen = 1;
	for (;;) {
	   continue2:
		if (tp>=maxp) {
			trp->lp = tp;
			tp = growtokenrow(trp);
			maxp = &trp->bp[trp->max];
		}
		tp->type = UNCLASS;
		tp->hideset = 0;
		tp->t = ip;
		tp->wslen = 0;
		tp->flag = 0;
		state = START;
		for (;;) {
			oldstate = state;
			c = *ip;
			if ((state = bigfsm[c][state]) >= 0) {
				ip += runelen;
				runelen = 1;
				continue;
			}
			state = ~state;
		reswitch:
			switch (state&0177) {
			case S_SELF:
				ip += runelen;
				runelen = 1;
			case S_SELFB:
				tp->type = GETACT(state);
				tp->len = ip - tp->t;
				tp++;
				goto continue2;

			case S_NAME:	/* like S_SELFB but with nmac check */
				tp->type = NAME;
				tp->len = ip - tp->t;
				nmac |= quicklook(tp->t[0], tp->len>1?tp->t[1]:0);
				tp++;
				goto continue2;

			case S_WS:
				tp->wslen = ip - tp->t;
				tp->t = ip;
				state = START;
				continue;

			default:
				if ((state&QBSBIT)==0) {
					ip += runelen;
					runelen = 1;
					continue;
				}
				state &= ~QBSBIT;
				s->inp = ip;
				if (c=='?') { 	/* check trigraph */
					if (trigraph(s)) {
						state = oldstate;
						continue;
					}
					goto reswitch;
				}
				if (c=='\\') { /* line-folding */
					if (foldline(s)) {
						s->lineinc++;
						state = oldstate;
						continue;
					}
					goto reswitch;
				}
				error(WARNING, "Lexical botch in cpp");
				ip += runelen;
				runelen = 1;
				continue;

			case S_EOB:
				s->inp = ip;
				fillbuf(cursource);
				state = oldstate;
				continue;

			case S_EOF:
				tp->type = END;
				tp->len = 0;
				s->inp = ip;
				if (tp!=trp->bp && (tp-1)->type!=NL && cursource->fd!=-1)
					error(WARNING,"No newline at end of file");
				trp->lp = tp+1;
				return nmac;

			case S_STNL:
				error(ERROR, "Unterminated string or char const");
			case S_NL:
				tp->t = ip;
				tp->type = NL;
				tp->len = 1;
				tp->wslen = 0;
				s->lineinc++;
				s->inp = ip+1;
				trp->lp = tp+1;
				return nmac;

			case S_EOFSTR:
				error(FATAL, "EOF in string or char constant");
				break;

			case S_COMNL:
				s->lineinc++;
				state = COM2;
				ip += runelen;
				runelen = 1;
				if (ip >= s->inb+(7*INS/8)) { /* very long comment */
					memmove(tp->t, ip, 4+s->inl-ip);
					s->inl -= ip-tp->t;
					ip = tp->t+1;
				}
				continue;

			case S_EOFCOM:
				error(WARNING, "EOF inside comment");
				--ip;
			case S_COMMENT:
				++ip;
				tp->t = ip;
				tp->t[-1] = ' ';
				tp->wslen = 1;
				state = START;
				continue;
			}
			break;
		}
		ip += runelen;
		runelen = 1;
		tp->len = ip - tp->t;
		tp++;
	}
}