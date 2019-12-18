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
typedef  union node {int dummy; } node ;

/* Variables and functions */
 union node* NEOF ; 
 int TEOF ; 
 int TNL ; 
 scalar_t__ checkkwd ; 
 int doprompt ; 
 int /*<<< orphan*/ * heredoclist ; 
 union node* list (int) ; 
 scalar_t__ needprompt ; 
 int /*<<< orphan*/  parser_temp_free_all () ; 
 int readtoken () ; 
 int /*<<< orphan*/  setprompt (int) ; 
 scalar_t__ tokpushback ; 

union node *
parsecmd(int interact)
{
	int t;

	/* This assumes the parser is not re-entered,
	 * which could happen if we add command substitution on PS1/PS2.
	 */
	parser_temp_free_all();
	heredoclist = NULL;

	tokpushback = 0;
	checkkwd = 0;
	doprompt = interact;
	if (doprompt)
		setprompt(1);
	else
		setprompt(0);
	needprompt = 0;
	t = readtoken();
	if (t == TEOF)
		return NEOF;
	if (t == TNL)
		return NULL;
	tokpushback++;
	return list(1);
}