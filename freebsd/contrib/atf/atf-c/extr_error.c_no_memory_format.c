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
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_error_is (int /*<<< orphan*/  const,char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*) ; 

__attribute__((used)) static
void
no_memory_format(const atf_error_t err, char *buf, size_t buflen)
{
    PRE(atf_error_is(err, "no_memory"));

    snprintf(buf, buflen, "Not enough memory");
}