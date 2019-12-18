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
struct TYPE_3__ {int type; int /*<<< orphan*/  keyword; int /*<<< orphan*/  id_kind; } ;
typedef  TYPE_1__ c_token ;

/* Variables and functions */
#define  CPP_KEYWORD 162 
#define  CPP_LESS 161 
#define  CPP_NAME 160 
#define  C_ID_CLASSNAME 159 
#define  C_ID_ID 158 
#define  C_ID_TYPENAME 157 
#define  RID_ATTRIBUTE 156 
#define  RID_AUTO 155 
#define  RID_BOOL 154 
#define  RID_CHAR 153 
#define  RID_COMPLEX 152 
#define  RID_CONST 151 
#define  RID_DFLOAT128 150 
#define  RID_DFLOAT32 149 
#define  RID_DFLOAT64 148 
#define  RID_DOUBLE 147 
#define  RID_ENUM 146 
#define  RID_EXTERN 145 
#define  RID_FLOAT 144 
#define  RID_INLINE 143 
#define  RID_INT 142 
#define  RID_LONG 141 
#define  RID_REGISTER 140 
#define  RID_RESTRICT 139 
#define  RID_SHORT 138 
#define  RID_SIGNED 137 
#define  RID_STATIC 136 
#define  RID_STRUCT 135 
#define  RID_THREAD 134 
#define  RID_TYPEDEF 133 
#define  RID_TYPEOF 132 
#define  RID_UNION 131 
#define  RID_UNSIGNED 130 
#define  RID_VOID 129 
#define  RID_VOLATILE 128 
 int /*<<< orphan*/  c_dialect_objc () ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static bool
c_token_starts_declspecs (c_token *token)
{
  switch (token->type)
    {
    case CPP_NAME:
      switch (token->id_kind)
	{
	case C_ID_ID:
	  return false;
	case C_ID_TYPENAME:
	  return true;
	case C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  return true;
	default:
	  gcc_unreachable ();
	}
    case CPP_KEYWORD:
      switch (token->keyword)
	{
	case RID_STATIC:
	case RID_EXTERN:
	case RID_REGISTER:
	case RID_TYPEDEF:
	case RID_INLINE:
	case RID_AUTO:
	case RID_THREAD:
	case RID_UNSIGNED:
	case RID_LONG:
	case RID_SHORT:
	case RID_SIGNED:
	case RID_COMPLEX:
	case RID_INT:
	case RID_CHAR:
	case RID_FLOAT:
	case RID_DOUBLE:
	case RID_VOID:
	case RID_DFLOAT32:
	case RID_DFLOAT64:
	case RID_DFLOAT128:
	case RID_BOOL:
	case RID_ENUM:
	case RID_STRUCT:
	case RID_UNION:
	case RID_TYPEOF:
	case RID_CONST:
	case RID_VOLATILE:
	case RID_RESTRICT:
	case RID_ATTRIBUTE:
	  return true;
	default:
	  return false;
	}
    case CPP_LESS:
      if (c_dialect_objc ())
	return true;
      return false;
    default:
      return false;
    }
}