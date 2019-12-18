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
struct TYPE_2__ {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Decl ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_STRUCT ; 
 int /*<<< orphan*/  DECL_UNION ; 
 int /*<<< orphan*/  TOKEN_POUND ; 
 int /*<<< orphan*/  const_keyword ; 
 int /*<<< orphan*/  enum_keyword ; 
 int /*<<< orphan*/  func_keyword ; 
 int /*<<< orphan*/  import_keyword ; 
 scalar_t__ match_keyword (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_decl_aggregate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_decl_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_decl_enum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_decl_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_decl_import (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_decl_note (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_decl_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_decl_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_keyword ; 
 TYPE_1__ token ; 
 int /*<<< orphan*/  typedef_keyword ; 
 int /*<<< orphan*/  union_keyword ; 
 int /*<<< orphan*/  var_keyword ; 

Decl *parse_decl_opt(void) {
    SrcPos pos = token.pos;
    if (match_keyword(enum_keyword)) {
        return parse_decl_enum(pos);
    } else if (match_keyword(struct_keyword)) {
        return parse_decl_aggregate(pos, DECL_STRUCT);
    } else if (match_keyword(union_keyword)) {
        return parse_decl_aggregate(pos, DECL_UNION);
    } else if (match_keyword(const_keyword)) {
        return parse_decl_const(pos);
    } else if (match_keyword(typedef_keyword)) {
        return parse_decl_typedef(pos);
    } else if (match_keyword(func_keyword)) {
        return parse_decl_func(pos);
    } else if (match_keyword(var_keyword)) {
        return parse_decl_var(pos);
    } else if (match_keyword(import_keyword)) {
        return parse_decl_import(pos);
    } else if (match_token(TOKEN_POUND)) {
        return parse_decl_note(pos);
    } else {
        return NULL;
    }
}