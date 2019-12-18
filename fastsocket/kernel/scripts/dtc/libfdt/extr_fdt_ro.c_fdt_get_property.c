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
typedef  int uint32_t ;
struct fdt_property {int /*<<< orphan*/  len; int /*<<< orphan*/  nameoff; } ;

/* Variables and functions */
#define  FDT_BEGIN_NODE 132 
#define  FDT_END 131 
#define  FDT_END_NODE 130 
 int FDT_ERR_BADSTRUCTURE ; 
 int FDT_ERR_NOTFOUND ; 
 int FDT_ERR_TRUNCATED ; 
#define  FDT_NOP 129 
#define  FDT_PROP 128 
 int _fdt_check_node_offset (void const*,int) ; 
 int fdt32_to_cpu (int /*<<< orphan*/ ) ; 
 int fdt_check_header (void const*) ; 
 int fdt_next_tag (void const*,int,int*) ; 
 struct fdt_property* fdt_offset_ptr (void const*,int,int) ; 
 int /*<<< orphan*/  fdt_string (void const*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

const struct fdt_property *fdt_get_property(const void *fdt,
					    int nodeoffset,
					    const char *name, int *lenp)
{
	uint32_t tag;
	const struct fdt_property *prop;
	int namestroff;
	int offset, nextoffset;
	int err;

	if (((err = fdt_check_header(fdt)) != 0)
	    || ((err = _fdt_check_node_offset(fdt, nodeoffset)) < 0))
			goto fail;

	nextoffset = err;
	do {
		offset = nextoffset;

		tag = fdt_next_tag(fdt, offset, &nextoffset);
		switch (tag) {
		case FDT_END:
			err = -FDT_ERR_TRUNCATED;
			goto fail;

		case FDT_BEGIN_NODE:
		case FDT_END_NODE:
		case FDT_NOP:
			break;

		case FDT_PROP:
			err = -FDT_ERR_BADSTRUCTURE;
			prop = fdt_offset_ptr(fdt, offset, sizeof(*prop));
			if (! prop)
				goto fail;
			namestroff = fdt32_to_cpu(prop->nameoff);
			if (strcmp(fdt_string(fdt, namestroff), name) == 0) {
				/* Found it! */
				int len = fdt32_to_cpu(prop->len);
				prop = fdt_offset_ptr(fdt, offset,
						      sizeof(*prop)+len);
				if (! prop)
					goto fail;

				if (lenp)
					*lenp = len;

				return prop;
			}
			break;

		default:
			err = -FDT_ERR_BADSTRUCTURE;
			goto fail;
		}
	} while ((tag != FDT_BEGIN_NODE) && (tag != FDT_END_NODE));

	err = -FDT_ERR_NOTFOUND;
 fail:
	if (lenp)
		*lenp = err;
	return NULL;
}