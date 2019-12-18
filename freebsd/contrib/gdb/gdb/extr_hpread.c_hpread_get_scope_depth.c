#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ index; } ;
struct TYPE_7__ {TYPE_2__ dnttp; } ;
struct TYPE_8__ {TYPE_3__ beginscope; } ;
struct TYPE_5__ {int kind; } ;
union dnttentry {TYPE_4__ dend; TYPE_1__ dblock; } ;
struct objfile {int dummy; } ;
struct dntt_type_block {int dummy; } ;

/* Variables and functions */
#define  DNTT_TYPE_BEGIN 135 
#define  DNTT_TYPE_CLASS_SCOPE 134 
#define  DNTT_TYPE_COMMON 133 
#define  DNTT_TYPE_DOC_FUNCTION 132 
#define  DNTT_TYPE_END 131 
#define  DNTT_TYPE_FUNCTION 130 
#define  DNTT_TYPE_MODULE 129 
#define  DNTT_TYPE_WITH 128 
 char* LNTT (struct objfile*) ; 
 union dnttentry* hpread_get_lntt (int,struct objfile*) ; 

__attribute__((used)) static int
hpread_get_scope_depth (union dnttentry *dn_bufp, struct objfile *objfile,
			int report_nested)
{
  int index;
  union dnttentry *dn_tmp;
  short depth = 0;
/****************************/
  return 0;
/****************************/

  index = (((char *) dn_bufp) - LNTT (objfile)) / (sizeof (struct dntt_type_block));

  while (--index >= 0)
    {
      dn_tmp = hpread_get_lntt (index, objfile);
      switch (dn_tmp->dblock.kind)
	{
	case DNTT_TYPE_MODULE:
	  return depth;
	case DNTT_TYPE_END:
	  /* index is signed int; dnttp.index is 29-bit unsigned int! */
	  index = (int) dn_tmp->dend.beginscope.dnttp.index;
	  break;
	case DNTT_TYPE_BEGIN:
	case DNTT_TYPE_FUNCTION:
	case DNTT_TYPE_DOC_FUNCTION:
	case DNTT_TYPE_WITH:
	case DNTT_TYPE_COMMON:
	case DNTT_TYPE_CLASS_SCOPE:
	  depth++;
	  if (report_nested)
	    return 1;
	  break;
	default:
	  break;
	}
    }
  return depth;
}