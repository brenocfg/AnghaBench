#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int is_incomplete; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  scalar_t__ DeclKind ;
typedef  TYPE_1__ Decl ;
typedef  int /*<<< orphan*/  AggregateKind ;

/* Variables and functions */
 int /*<<< orphan*/  AGGREGATE_STRUCT ; 
 int /*<<< orphan*/  AGGREGATE_UNION ; 
 scalar_t__ DECL_STRUCT ; 
 scalar_t__ DECL_UNION ; 
 int /*<<< orphan*/  TOKEN_SEMICOLON ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_aggregate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* new_decl_aggregate (int /*<<< orphan*/ ,scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_aggregate (int /*<<< orphan*/ ) ; 
 char* parse_name () ; 

Decl *parse_decl_aggregate(SrcPos pos, DeclKind kind) {
    assert(kind == DECL_STRUCT || kind == DECL_UNION);
    const char *name = parse_name();
    AggregateKind aggregate_kind = kind == DECL_STRUCT ? AGGREGATE_STRUCT : AGGREGATE_UNION;
    if (match_token(TOKEN_SEMICOLON)) {
        Decl *decl = new_decl_aggregate(pos, kind, name, new_aggregate(pos, aggregate_kind, NULL, 0));
        decl->is_incomplete = true;
        return decl;
    } else {
        return new_decl_aggregate(pos, kind, name, parse_aggregate(aggregate_kind));
    }
}