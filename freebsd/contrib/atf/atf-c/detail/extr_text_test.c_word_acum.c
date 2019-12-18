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
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 

__attribute__((used)) static
atf_error_t
word_acum(const char *word, void *data)
{
    char *acum = data;

    strcat(acum, word);

    return atf_no_error();
}