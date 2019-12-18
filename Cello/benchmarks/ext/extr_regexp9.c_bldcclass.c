#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* spans; char* end; } ;
typedef  char Rune ;

/* Variables and functions */
 int CCLASS ; 
 int NCCLASS ; 
 int NCCRUNE ; 
 TYPE_1__* newclass () ; 
 int nextc (char*) ; 
 int /*<<< orphan*/  rcerror (char*) ; 
 TYPE_1__* yyclassp ; 

__attribute__((used)) static int
bldcclass(void)
{
	int type;
	Rune r[NCCRUNE];
	Rune *p, *ep, *np;
	Rune rune;
	int quoted;

	/* we have already seen the '[' */
	type = CCLASS;
	yyclassp = newclass();

	/* look ahead for negation */
	/* SPECIAL CASE!!! negated classes don't match \n */
	ep = r;
	quoted = nextc(&rune);
	if(!quoted && rune == '^'){
		type = NCCLASS;
		quoted = nextc(&rune);
		*ep++ = '\n';
		*ep++ = '\n';
	}

	/* parse class into a set of spans */
	for(; ep<&r[NCCRUNE];){
		if(rune == 0){
			rcerror("malformed '[]'");
			return 0;
		}
		if(!quoted && rune == ']')
			break;
		if(!quoted && rune == '-'){
			if(ep == r){
				rcerror("malformed '[]'");
				return 0;
			}
			quoted = nextc(&rune);
			if((!quoted && rune == ']') || rune == 0){
				rcerror("malformed '[]'");
				return 0;
			}
			*(ep-1) = rune;
		} else {
			*ep++ = rune;
			*ep++ = rune;
		}
		quoted = nextc(&rune);
	}

	/* sort on span start */
	for(p = r; p < ep; p += 2){
		for(np = p; np < ep; np += 2)
			if(*np < *p){
				rune = np[0];
				np[0] = p[0];
				p[0] = rune;
				rune = np[1];
				np[1] = p[1];
				p[1] = rune;
			}
	}

	/* merge spans */
	np = yyclassp->spans;
	p = r;
	if(r == ep)
		yyclassp->end = np;
	else {
		np[0] = *p++;
		np[1] = *p++;
		for(; p < ep; p += 2)
			if(p[0] <= np[1]){
				if(p[1] > np[1])
					np[1] = p[1];
			} else {
				np += 2;
				np[0] = p[0];
				np[1] = p[1];
			}
		yyclassp->end = np+2;
	}

	return type;
}