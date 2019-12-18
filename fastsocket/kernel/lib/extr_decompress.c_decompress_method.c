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
struct compress_format {char* name; int /*<<< orphan*/ * decompressor; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/ * decompress_fn ;

/* Variables and functions */
 struct compress_format* compressed_formats ; 
 int /*<<< orphan*/  memcmp (unsigned char const*,int /*<<< orphan*/ ,int) ; 

decompress_fn decompress_method(const unsigned char *inbuf, int len,
				const char **name)
{
	const struct compress_format *cf;

	if (len < 2)
		return NULL;	/* Need at least this much... */

	for (cf = compressed_formats; cf->name; cf++) {
		if (!memcmp(inbuf, cf->magic, 2))
			break;

	}
	if (name)
		*name = cf->name;
	return cf->decompressor;
}