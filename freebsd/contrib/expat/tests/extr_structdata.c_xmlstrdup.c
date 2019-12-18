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
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int xcstrlen (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static XML_Char *
xmlstrdup(const XML_Char *s)
{
    size_t byte_count = (xcstrlen(s) + 1) * sizeof(XML_Char);
    XML_Char *dup = malloc(byte_count);

    assert(dup != NULL);
    memcpy(dup, s, byte_count);
    return dup;
}