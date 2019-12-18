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
struct vector_str {int /*<<< orphan*/ * container; } ;

/* Variables and functions */
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

char *
vector_str_substr(const struct vector_str *v, size_t begin, size_t end,
    size_t *r_len)
{
	size_t cur, i, len;
	char *rtn;

	if (v == NULL || begin > end)
		return (NULL);

	len = 0;
	for (i = begin; i < end + 1; ++i)
		len += strlen(v->container[i]);

	if ((rtn = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);

	if (r_len != NULL)
		*r_len = len;

	cur = 0;
	for (i = begin; i < end + 1; ++i) {
		len = strlen(v->container[i]);
		memcpy(rtn + cur, v->container[i], len);
		cur += len;
	}
	rtn[cur] = '\0';

	return (rtn);
}