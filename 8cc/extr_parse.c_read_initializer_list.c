#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_14__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;
struct TYPE_15__ {scalar_t__ kind; int /*<<< orphan*/  sval; } ;
typedef  TYPE_2__ Token ;
struct TYPE_16__ {scalar_t__ kind; } ;

/* Variables and functions */
 scalar_t__ KIND_ARRAY ; 
 scalar_t__ KIND_STRUCT ; 
 scalar_t__ TSTRING ; 
 int /*<<< orphan*/  assign_string (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_2__* get () ; 
 scalar_t__ is_keyword (TYPE_2__*,char) ; 
 scalar_t__ is_string (TYPE_1__*) ; 
 TYPE_1__* make_array_type (TYPE_1__*,int) ; 
 TYPE_7__* peek () ; 
 int /*<<< orphan*/  read_array_initializer (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  read_struct_initializer (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  unget_token (TYPE_2__*) ; 

__attribute__((used)) static void read_initializer_list(Vector *inits, Type *ty, int off, bool designated) {
    Token *tok = get();
    if (is_string(ty)) {
        if (tok->kind == TSTRING) {
            assign_string(inits, ty, tok->sval, off);
            return;
        }
        if (is_keyword(tok, '{') && peek()->kind == TSTRING) {
            tok = get();
            assign_string(inits, ty, tok->sval, off);
            expect('}');
            return;
        }
    }
    unget_token(tok);
    if (ty->kind == KIND_ARRAY) {
        read_array_initializer(inits, ty, off, designated);
    } else if (ty->kind == KIND_STRUCT) {
        read_struct_initializer(inits, ty, off, designated);
    } else {
        Type *arraytype = make_array_type(ty, 1);
        read_array_initializer(inits, arraytype, off, designated);
    }
}