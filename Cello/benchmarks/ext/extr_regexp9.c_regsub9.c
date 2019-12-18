#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* ep; } ;
struct TYPE_5__ {char* sp; } ;
struct TYPE_7__ {TYPE_2__ e; TYPE_1__ s; } ;
typedef  TYPE_3__ Resub ;

/* Variables and functions */

extern	void
regsub9(char *sp,	/* source string */
	char *dp,	/* destination string */
	int dlen,
	Resub *mp,	/* subexpression elements */
	int ms)		/* number of elements pointed to by mp */
{
	char *ssp, *ep;
	int i;

	ep = dp+dlen-1;
	while(*sp != '\0'){
		if(*sp == '\\'){
			switch(*++sp){
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				i = *sp-'0';
				if(mp[i].s.sp != 0 && mp!=0 && ms>i)
					for(ssp = mp[i].s.sp;
					     ssp < mp[i].e.ep;
					     ssp++)
						if(dp < ep)
							*dp++ = *ssp;
				break;
			case '\\':
				if(dp < ep)
					*dp++ = '\\';
				break;
			case '\0':
				sp--;
				break;
			default:
				if(dp < ep)
					*dp++ = *sp;
				break;
			}
		}else if(*sp == '&'){				
			if(mp[0].s.sp != 0 && mp!=0 && ms>0)
			if(mp[0].s.sp != 0)
				for(ssp = mp[0].s.sp;
				     ssp < mp[0].e.ep; ssp++)
					if(dp < ep)
						*dp++ = *ssp;
		}else{
			if(dp < ep)
				*dp++ = *sp;
		}
		sp++;
	}
	*dp = '\0';
}