#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Notes ;
typedef  int /*<<< orphan*/  Note ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_AT ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_notes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_note () ; 

Notes parse_notes(void) {
    Note *notes = NULL;
    while (match_token(TOKEN_AT)) {
        buf_push(notes, parse_note());
    }
    return new_notes(notes, buf_len(notes));
}