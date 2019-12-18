#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* type; struct TYPE_6__* scope; } ;
struct TYPE_5__ {int first_line; int first_column; int last_line; int last_column; } ;
struct TYPE_4__ {TYPE_3__* scope; TYPE_3__* type; TYPE_3__* dlist; TYPE_3__* decl; TYPE_3__* code; TYPE_3__* expr; TYPE_3__* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_2__* loc ; 
 char* msg ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int) ; 
 int psymb ; 
 TYPE_1__* val ; 

__attribute__((used)) static void
YYDESTRUCT_DECL()
{
    switch (psymb)
    {
	case 43:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 681 "btyacc_demo.tab.c"
	case 45:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 690 "btyacc_demo.tab.c"
	case 42:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 699 "btyacc_demo.tab.c"
	case 47:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 708 "btyacc_demo.tab.c"
	case 37:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 717 "btyacc_demo.tab.c"
	case 257:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 726 "btyacc_demo.tab.c"
	case 258:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 735 "btyacc_demo.tab.c"
	case 40:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 744 "btyacc_demo.tab.c"
	case 91:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 753 "btyacc_demo.tab.c"
	case 46:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 762 "btyacc_demo.tab.c"
	case 259:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).id); }
	break;
#line 771 "btyacc_demo.tab.c"
	case 260:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).expr); }
	break;
#line 780 "btyacc_demo.tab.c"
	case 261:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 789 "btyacc_demo.tab.c"
	case 262:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 798 "btyacc_demo.tab.c"
	case 263:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 807 "btyacc_demo.tab.c"
	case 264:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 816 "btyacc_demo.tab.c"
	case 265:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 825 "btyacc_demo.tab.c"
	case 266:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 834 "btyacc_demo.tab.c"
	case 267:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 843 "btyacc_demo.tab.c"
	case 268:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 852 "btyacc_demo.tab.c"
	case 269:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 861 "btyacc_demo.tab.c"
	case 59:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 870 "btyacc_demo.tab.c"
	case 44:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 879 "btyacc_demo.tab.c"
	case 41:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 888 "btyacc_demo.tab.c"
	case 93:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 897 "btyacc_demo.tab.c"
	case 123:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 906 "btyacc_demo.tab.c"
	case 125:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 915 "btyacc_demo.tab.c"
	case 270:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 924 "btyacc_demo.tab.c"
	case 271:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 933 "btyacc_demo.tab.c"
	case 272:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).expr); }
	break;
#line 942 "btyacc_demo.tab.c"
	case 273:
#line 67 "btyacc_demo.y"
	{ /* 'msg' is a 'char *' indicating the context of destructor invocation*/
		  printf("%s accessed by symbol \"decl\" (case s.b. 273) @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).decl->scope); free((*val).decl->type); }
	break;
#line 952 "btyacc_demo.tab.c"
	case 274:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 961 "btyacc_demo.tab.c"
	case 275:
#line 83 "btyacc_demo.y"
	{ printf("%s accessed by symbol with no type @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  /* in this example, we don't know what to do here */ }
	break;
#line 970 "btyacc_demo.tab.c"
	case 276:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).code); }
	break;
#line 979 "btyacc_demo.tab.c"
	case 277:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).code); }
	break;
#line 988 "btyacc_demo.tab.c"
	case 278:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).code); }
	break;
#line 997 "btyacc_demo.tab.c"
	case 279:
#line 73 "btyacc_demo.y"
	{ printf("%s accessed by symbol with type <decl> (case s.b. 279 & 280) @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).decl); }
	break;
#line 1006 "btyacc_demo.tab.c"
	case 280:
#line 73 "btyacc_demo.y"
	{ printf("%s accessed by symbol with type <decl> (case s.b. 279 & 280) @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).decl); }
	break;
#line 1015 "btyacc_demo.tab.c"
	case 281:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).type); }
	break;
#line 1024 "btyacc_demo.tab.c"
	case 282:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).type); }
	break;
#line 1033 "btyacc_demo.tab.c"
	case 283:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).type); }
	break;
#line 1042 "btyacc_demo.tab.c"
	case 284:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).type); }
	break;
#line 1051 "btyacc_demo.tab.c"
	case 285:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).type); }
	break;
#line 1060 "btyacc_demo.tab.c"
	case 286:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).scope); }
	break;
#line 1069 "btyacc_demo.tab.c"
	case 287:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).dlist); }
	break;
#line 1078 "btyacc_demo.tab.c"
	case 288:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).dlist); }
	break;
#line 1087 "btyacc_demo.tab.c"
	case 289:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).scope); }
	break;
#line 1096 "btyacc_demo.tab.c"
	case 290:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).scope); }
	break;
#line 1105 "btyacc_demo.tab.c"
	case 291:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).scope); }
	break;
#line 1114 "btyacc_demo.tab.c"
	case 292:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).scope); }
	break;
#line 1123 "btyacc_demo.tab.c"
	case 293:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).type); }
	break;
#line 1132 "btyacc_demo.tab.c"
	case 294:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).scope); }
	break;
#line 1141 "btyacc_demo.tab.c"
	case 295:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).type); }
	break;
#line 1150 "btyacc_demo.tab.c"
	case 296:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).scope); }
	break;
#line 1159 "btyacc_demo.tab.c"
	case 297:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).scope); }
	break;
#line 1168 "btyacc_demo.tab.c"
	case 298:
#line 78 "btyacc_demo.y"
	{ printf("%s accessed by symbol of any type other than <decl>  @ position[%d,%d..%d,%d]\n",
			 msg,
			 (*loc).first_line, (*loc).first_column,
			 (*loc).last_line, (*loc).last_column);
		  free((*val).scope); }
	break;
#line 1177 "btyacc_demo.tab.c"
    }
}