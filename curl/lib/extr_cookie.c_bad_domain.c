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

/* Variables and functions */
 int /*<<< orphan*/  strcasecompare (char const*,char*) ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 

__attribute__((used)) static bool bad_domain(const char *domain)
{
  return !strchr(domain, '.') && !strcasecompare(domain, "localhost");
}