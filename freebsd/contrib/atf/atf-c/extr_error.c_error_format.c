#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* atf_error_t ;
struct TYPE_3__ {char* m_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 

__attribute__((used)) static
void
error_format(const atf_error_t err, char *buf, size_t buflen)
{
    PRE(err != NULL);
    snprintf(buf, buflen, "Error '%s'", err->m_type);
}