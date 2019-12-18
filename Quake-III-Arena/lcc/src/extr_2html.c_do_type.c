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
typedef  TYPE_1__* rcc_type_ty ;
struct TYPE_3__ {int kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY ; 
 int /*<<< orphan*/  CONST ; 
 int /*<<< orphan*/  ENUM ; 
 int /*<<< orphan*/  FLOAT ; 
 int /*<<< orphan*/  FUNCTION ; 
 int /*<<< orphan*/  INT ; 
 int /*<<< orphan*/  POINTER ; 
 int /*<<< orphan*/  STRUCT ; 
 int /*<<< orphan*/  UNION ; 
 int /*<<< orphan*/  UNSIGNED ; 
 int /*<<< orphan*/  VOID ; 
 int /*<<< orphan*/  VOLATILE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caselabel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enum_list ; 
 int /*<<< orphan*/  field_list ; 
 int /*<<< orphan*/  fields ; 
 int /*<<< orphan*/  formals ; 
 int /*<<< orphan*/  identifier ; 
 int /*<<< orphan*/  ids ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tag ; 
 int /*<<< orphan*/  type ; 
 int /*<<< orphan*/  uid ; 
 int /*<<< orphan*/  uid_list ; 
 int /*<<< orphan*/  yy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_type(rcc_type_ty x) {
#define attributes xx(x,size,int); xx(x,align,int)
	switch (x->kind) {
	static char *typename = "type";
	caselabel(INT); break;
	caselabel(UNSIGNED); break;
	caselabel(FLOAT); break;
	caselabel(VOID); break;
	caselabel(POINTER);
		yy(POINTER,type,uid);
		break;
	caselabel(ENUM);
		yy(ENUM,tag,identifier);
		yy(ENUM,ids,enum_list);
		break;
	caselabel(STRUCT);
		yy(STRUCT,tag,identifier);
		yy(STRUCT,fields,field_list);
		break;
	caselabel(UNION);
		yy(UNION,tag,identifier);
		yy(UNION,fields,field_list);
		break;
	caselabel(ARRAY);
		yy(ARRAY,type,uid);
		break;
	caselabel(FUNCTION);
		yy(FUNCTION,type,uid);
		yy(FUNCTION,formals,uid_list);
		break;
	caselabel(CONST);
		yy(CONST,type,uid);
		break;
	caselabel(VOLATILE);
		yy(VOLATILE,type,uid);
		break;
	default: assert(0);
	}
#undef attributes
	printf("</ul>\n");
}