#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* sval; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * ast_label (char*) ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  labels ; 
 scalar_t__ map_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_label_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 

__attribute__((used)) static Node *read_label(Token *tok) {
    char *label = tok->sval;
    if (map_get(labels, label))
        errort(tok, "duplicate label: %s", tok2s(tok));
    Node *r = ast_label(label);
    map_put(labels, label, r);
    return read_label_tail(r);
}