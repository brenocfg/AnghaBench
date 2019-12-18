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
typedef  void* tree ;
struct c_typespec {void* spec; void* kind; } ;
struct c_declspecs {int type_seen_p; } ;
typedef  int /*<<< orphan*/  c_parser ;
typedef  scalar_t__ c_id_kind ;
struct TYPE_2__ {scalar_t__ id_kind; int keyword; void* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_KEYWORD ; 
 int /*<<< orphan*/  CPP_LESS ; 
 int /*<<< orphan*/  CPP_NAME ; 
 scalar_t__ C_ID_CLASSNAME ; 
 scalar_t__ C_ID_TYPENAME ; 
 void* NULL_TREE ; 
 int /*<<< orphan*/  OBJC_NEED_RAW_IDENTIFIER (int) ; 
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
 scalar_t__ c_dialect_objc () ; 
 void* c_parser_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 struct c_typespec c_parser_enum_specifier (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* c_parser_objc_protocol_refs (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 struct c_typespec c_parser_struct_or_union_specifier (int /*<<< orphan*/ *) ; 
 struct c_typespec c_parser_typeof_specifier (int /*<<< orphan*/ *) ; 
 void* ctsk_objc ; 
 void* ctsk_resword ; 
 void* ctsk_typedef ; 
 int /*<<< orphan*/  declspecs_add_attrs (struct c_declspecs*,void*) ; 
 int /*<<< orphan*/  declspecs_add_qual (struct c_declspecs*,void*) ; 
 int /*<<< orphan*/  declspecs_add_scspec (struct c_declspecs*,void*) ; 
 int /*<<< orphan*/  declspecs_add_type (struct c_declspecs*,struct c_typespec) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 void* lookup_name (void*) ; 
 void* objc_get_protocol_qualified_type (void*,void*) ; 

__attribute__((used)) static void
c_parser_declspecs (c_parser *parser, struct c_declspecs *specs,
		    bool scspec_ok, bool typespec_ok, bool start_attr_ok)
{
  bool attrs_ok = start_attr_ok;
  bool seen_type = specs->type_seen_p;
  while (c_parser_next_token_is (parser, CPP_NAME)
	 || c_parser_next_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_next_token_is (parser, CPP_LESS)))
    {
      struct c_typespec t;
      tree attrs;
      if (c_parser_next_token_is (parser, CPP_NAME))
	{
	  tree value = c_parser_peek_token (parser)->value;
	  c_id_kind kind = c_parser_peek_token (parser)->id_kind;
	  /* This finishes the specifiers unless a type name is OK, it
	     is declared as a type name and a type name hasn't yet
	     been seen.  */
	  if (!typespec_ok || seen_type
	      || (kind != C_ID_TYPENAME && kind != C_ID_CLASSNAME))
	    break;
	  c_parser_consume_token (parser);
	  seen_type = true;
	  attrs_ok = true;
	  if (kind == C_ID_TYPENAME
	      && (!c_dialect_objc ()
		  || c_parser_next_token_is_not (parser, CPP_LESS)))
	    {
	      t.kind = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (value);
	    }
	  else
	    {
	      tree proto = NULL_TREE;
	      gcc_assert (c_dialect_objc ());
	      t.kind = ctsk_objc;
	      if (c_parser_next_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (value, proto);
	    }
	  declspecs_add_type (specs, t);
	  continue;
	}
      if (c_parser_next_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  tree proto;
	  gcc_assert (c_dialect_objc ());
	  if (!typespec_ok || seen_type)
	    break;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.kind = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_TREE, proto);
	  declspecs_add_type (specs, t);
	  continue;
	}
      gcc_assert (c_parser_next_token_is (parser, CPP_KEYWORD));
      switch (c_parser_peek_token (parser)->keyword)
	{
	case RID_STATIC:
	case RID_EXTERN:
	case RID_REGISTER:
	case RID_TYPEDEF:
	case RID_INLINE:
	case RID_AUTO:
	case RID_THREAD:
	  if (!scspec_ok)
	    goto out;
	  attrs_ok = true;
	  /* TODO: Distinguish between function specifiers (inline)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_add_scspec (specs, c_parser_peek_token (parser)->value);
	  c_parser_consume_token (parser);
	  break;
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
	  if (!typespec_ok)
	    goto out;
	  attrs_ok = true;
	  seen_type = true;
	  OBJC_NEED_RAW_IDENTIFIER (1);
	  t.kind = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->value;
	  declspecs_add_type (specs, t);
	  c_parser_consume_token (parser);
	  break;
	case RID_ENUM:
	  if (!typespec_ok)
	    goto out;
	  attrs_ok = true;
	  seen_type = true;
	  t = c_parser_enum_specifier (parser);
	  declspecs_add_type (specs, t);
	  break;
	case RID_STRUCT:
	case RID_UNION:
	  if (!typespec_ok)
	    goto out;
	  attrs_ok = true;
	  seen_type = true;
	  t = c_parser_struct_or_union_specifier (parser);
	  declspecs_add_type (specs, t);
	  break;
	case RID_TYPEOF:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  if (!typespec_ok || seen_type)
	    goto out;
	  attrs_ok = true;
	  seen_type = true;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_add_type (specs, t);
	  break;
	case RID_CONST:
	case RID_VOLATILE:
	case RID_RESTRICT:
	  attrs_ok = true;
	  declspecs_add_qual (specs, c_parser_peek_token (parser)->value);
	  c_parser_consume_token (parser);
	  break;
	case RID_ATTRIBUTE:
	  if (!attrs_ok)
	    goto out;
	  attrs = c_parser_attributes (parser);
	  declspecs_add_attrs (specs, attrs);
	  break;
	default:
	  goto out;
	}
    }
 out: ;
}