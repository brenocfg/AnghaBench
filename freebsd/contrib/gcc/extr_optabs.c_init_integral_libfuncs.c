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
typedef  int /*<<< orphan*/  optab ;

/* Variables and functions */
 int BITS_PER_WORD ; 
 int LONG_LONG_TYPE_SIZE ; 
 int /*<<< orphan*/  MODE_INT ; 
 int /*<<< orphan*/  init_libfuncs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  mode_for_size (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  word_mode ; 

__attribute__((used)) static void
init_integral_libfuncs (optab optable, const char *opname, int suffix)
{
  int maxsize = 2*BITS_PER_WORD;
  if (maxsize < LONG_LONG_TYPE_SIZE)
    maxsize = LONG_LONG_TYPE_SIZE;
  init_libfuncs (optable, word_mode,
		 mode_for_size (maxsize, MODE_INT, 0),
		 opname, suffix);
}