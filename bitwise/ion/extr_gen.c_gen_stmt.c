#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_21__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_39__ {long long ll; } ;
typedef  TYPE_8__ Val ;
struct TYPE_40__ {TYPE_14__* start; TYPE_14__* end; } ;
struct TYPE_32__ {int /*<<< orphan*/  stmts; } ;
struct TYPE_38__ {TYPE_21__ block; TYPE_12__* next; TYPE_14__* cond; TYPE_12__* init; } ;
struct TYPE_37__ {TYPE_14__* cond; TYPE_21__ block; } ;
struct TYPE_36__ {size_t num_elseifs; TYPE_12__* init; TYPE_21__ else_block; TYPE_15__* elseifs; TYPE_21__ then_block; TYPE_14__* cond; } ;
struct TYPE_35__ {int /*<<< orphan*/  name; } ;
struct TYPE_34__ {char* name; int /*<<< orphan*/  pos; TYPE_14__* expr; } ;
struct TYPE_33__ {char* val; } ;
struct TYPE_31__ {size_t num_cases; TYPE_10__* cases; TYPE_14__* expr; } ;
struct TYPE_30__ {TYPE_21__ block; TYPE_14__* cond; } ;
struct TYPE_29__ {TYPE_2__ str_lit; int /*<<< orphan*/  pos; int /*<<< orphan*/  kind; } ;
struct TYPE_28__ {int num_args; int /*<<< orphan*/  pos; TYPE_3__* args; int /*<<< orphan*/  name; } ;
struct TYPE_27__ {int kind; int /*<<< orphan*/  label; TYPE_1__ switch_stmt; TYPE_7__ for_stmt; TYPE_6__ while_stmt; TYPE_5__ if_stmt; TYPE_4__ init; int /*<<< orphan*/  pos; TYPE_13__ note; TYPE_21__ block; TYPE_14__* expr; } ;
struct TYPE_26__ {size_t num_stmts; TYPE_12__** stmts; } ;
struct TYPE_25__ {size_t num_patterns; TYPE_11__ block; int /*<<< orphan*/  is_default; TYPE_9__* patterns; } ;
typedef  TYPE_9__ SwitchCasePattern ;
typedef  TYPE_10__ SwitchCase ;
typedef  TYPE_11__ StmtList ;
typedef  TYPE_12__ Stmt ;
typedef  TYPE_13__ Note ;
typedef  TYPE_14__ Expr ;
typedef  TYPE_15__ ElseIf ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_STR ; 
#define  STMT_BLOCK 139 
#define  STMT_BREAK 138 
#define  STMT_CONTINUE 137 
#define  STMT_DO_WHILE 136 
#define  STMT_FOR 135 
#define  STMT_GOTO 134 
#define  STMT_IF 133 
#define  STMT_LABEL 132 
#define  STMT_NOTE 131 
#define  STMT_RETURN 130 
#define  STMT_SWITCH 129 
#define  STMT_WHILE 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_name ; 
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  complete_name ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  foreign_name ; 
 int /*<<< orphan*/  gen_buf_pos (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_char (int) ; 
 int /*<<< orphan*/  gen_expr (TYPE_14__*) ; 
 int /*<<< orphan*/  gen_indent ; 
 int /*<<< orphan*/  gen_postamble_buf ; 
 int /*<<< orphan*/  gen_preamble_buf ; 
 int /*<<< orphan*/  gen_simple_stmt (TYPE_12__*) ; 
 int /*<<< orphan*/  gen_stmt_block (TYPE_21__) ; 
 int /*<<< orphan*/  gen_sync_pos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genf (char*,...) ; 
 int /*<<< orphan*/  genln () ; 
 int /*<<< orphan*/  genlnf (char*,...) ; 
 TYPE_8__ get_resolved_val (TYPE_14__*) ; 
 TYPE_13__* get_stmt_note (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_char_lit (TYPE_14__*) ; 
 char* str_intern (char*) ; 

void gen_stmt(Stmt *stmt) {
    gen_sync_pos(stmt->pos);
    switch (stmt->kind) {
    case STMT_RETURN:
        genlnf("return");
        if (stmt->expr) {
            genf(" ");
            gen_expr(stmt->expr);
        }
        genf(";");
        break;
    case STMT_BREAK:
        genlnf("break;");
        break;
    case STMT_CONTINUE:
        genlnf("continue;");
        break;
    case STMT_BLOCK:
        genln();
        gen_stmt_block(stmt->block);
        break;
    case STMT_NOTE: {
        Note note = stmt->note;
        if (note.name == assert_name) {
            genlnf("assert(");
            assert(note.num_args == 1);
            gen_expr(note.args[0].expr);
            genf(");");
        } else if (note.name == foreign_name) {
            const char *preamble_name = str_intern("preamble");
            const char *postamble_name = str_intern("postamble");
            for (size_t i = 0; i < note.num_args; i++) {
                const char *name = note.args[i].name;
                Expr *expr = note.args[i].expr;
                if (expr->kind != EXPR_STR) {
                    fatal_error(expr->pos, "#foreign argument must be a string");
                }
                const char *str = expr->str_lit.val;
                if (name == preamble_name) {
                    gen_buf_pos(&gen_preamble_buf, note.args[i].pos);
                    buf_printf(gen_preamble_buf, "%s\n", str);
                } else if (name == postamble_name) {
                    gen_buf_pos(&gen_postamble_buf, note.args[i].pos);
                    buf_printf(gen_postamble_buf, "%s\n", str);
                }
            }
        }
        break;
    }
    case STMT_IF:
        if (stmt->if_stmt.init) {
            genlnf("{");
            gen_indent++;
            gen_stmt(stmt->if_stmt.init);
        }
        gen_sync_pos(stmt->pos);
        genlnf("if (");
        if (stmt->if_stmt.cond) {
            gen_expr(stmt->if_stmt.cond);
        } else {
            genf("%s", stmt->if_stmt.init->init.name);
        }
        genf(") ");
        gen_stmt_block(stmt->if_stmt.then_block);
        for (size_t i = 0; i < stmt->if_stmt.num_elseifs; i++) {
            ElseIf elseif = stmt->if_stmt.elseifs[i];
            genf(" else if (");
            gen_expr(elseif.cond);
            genf(") ");
            gen_stmt_block(elseif.block);
        }
        if (stmt->if_stmt.else_block.stmts) {
            genf(" else ");
            gen_stmt_block(stmt->if_stmt.else_block);
        } else {
            Note *complete_note = get_stmt_note(stmt, complete_name);
            if (complete_note) {
                genf(" else {");
                gen_indent++;
                gen_sync_pos(complete_note->pos);
                genlnf("assert(\"@complete if/elseif chain failed to handle case\" && 0);");
                gen_indent--;
                genlnf("}");
            }
        }
        if (stmt->if_stmt.init) {
            gen_indent--;
            genlnf("}");
        }
        break;
    case STMT_WHILE:
        genlnf("while (");
        gen_expr(stmt->while_stmt.cond);
        genf(") ");
        gen_stmt_block(stmt->while_stmt.block);
        break;
    case STMT_DO_WHILE:
        genlnf("do ");
        gen_stmt_block(stmt->while_stmt.block);
        genf(" while (");
        gen_expr(stmt->while_stmt.cond);
        genf(");");
        break;
    case STMT_FOR:
        genlnf("for (");
        if (stmt->for_stmt.init) {
            gen_simple_stmt(stmt->for_stmt.init);
        }
        genf(";");
        if (stmt->for_stmt.cond) {
            genf(" ");
            gen_expr(stmt->for_stmt.cond);
        }
        genf(";");
        if (stmt->for_stmt.next) {
            genf(" ");
            gen_simple_stmt(stmt->for_stmt.next);
        }
        genf(") ");
        gen_stmt_block(stmt->for_stmt.block);
        break;
    case STMT_SWITCH: {
        genlnf("switch (");
        gen_expr(stmt->switch_stmt.expr);
        genf(") {");
        bool has_default = false;
        for (size_t i = 0; i < stmt->switch_stmt.num_cases; i++) {
            SwitchCase switch_case = stmt->switch_stmt.cases[i];
            for (size_t j = 0; j < switch_case.num_patterns; j++) {
                SwitchCasePattern pattern = switch_case.patterns[j];
                if (pattern.end) {
                    Val start_val = get_resolved_val(pattern.start);
                    Val end_val = get_resolved_val(pattern.end);
                    if (is_char_lit(pattern.start) && is_char_lit(pattern.end)) {
                        genln();
                        for (int c = (int)start_val.ll; c <= (int)end_val.ll; c++) {
                            genf("case ");
                            gen_char(c);
                            genf(": ");
                        } 
                    } else {
                        genlnf("// ");
                        gen_expr(pattern.start);
                        genf("...");
                        gen_expr(pattern.end);
                        genln();
                        for (long long ll = start_val.ll; ll <= end_val.ll; ll++) {
                            genf("case %lld: ", ll);
                        }
                    }
                } else {
                    genlnf("case ");
                    gen_expr(pattern.start);
                    genf(":");
                }
            }
            if (switch_case.is_default) {
                has_default = true;
                genlnf("default:");
            }
            genf(" ");
            genf("{");
            gen_indent++;
            StmtList block = switch_case.block;
            for (size_t j = 0; j < block.num_stmts; j++) {
                gen_stmt(block.stmts[j]);
            }
            genlnf("break;");
            gen_indent--;
            genlnf("}");
        }
        if (!has_default) {
            Note *note = get_stmt_note(stmt, complete_name);
            if (note) {
                genlnf("default:");
                gen_indent++;
                genlnf("assert(\"@complete switch failed to handle case\" && 0);");
                genlnf("break;");
                gen_indent--;
            }
        }
        genlnf("}");
        break;
    }
    case STMT_LABEL:
        genlnf("%s: ;", stmt->label);
        break;
    case STMT_GOTO:
        genlnf("goto %s;", stmt->label);
        break;
    default:
        genln();
        gen_simple_stmt(stmt);
        genf(";");
        break;
    }
}