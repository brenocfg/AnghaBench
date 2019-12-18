#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * workspace; int /*<<< orphan*/ * next_out; } ;
struct ppp_deflate_state {int w_size; TYPE_1__ strm; } ;

/* Variables and functions */
 int CILEN_DEFLATE ; 
 unsigned char CI_DEFLATE ; 
 unsigned char CI_DEFLATE_DRAFT ; 
 unsigned char DEFLATE_CHK_SEQUENCE ; 
 int DEFLATE_MAX_SIZE ; 
 scalar_t__ DEFLATE_METHOD (unsigned char) ; 
 scalar_t__ DEFLATE_METHOD_VAL ; 
 int DEFLATE_MIN_SIZE ; 
 int DEFLATE_SIZE (unsigned char) ; 
 int GFP_KERNEL ; 
 scalar_t__ Z_OK ; 
 int __GFP_REPEAT ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int) ; 
 struct ppp_deflate_state* kzalloc (int,int) ; 
 int /*<<< orphan*/  z_decomp_free (struct ppp_deflate_state*) ; 
 scalar_t__ zlib_inflateInit2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zlib_inflate_workspacesize () ; 

__attribute__((used)) static void *z_decomp_alloc(unsigned char *options, int opt_len)
{
	struct ppp_deflate_state *state;
	int w_size;

	if (opt_len != CILEN_DEFLATE
	    || (options[0] != CI_DEFLATE && options[0] != CI_DEFLATE_DRAFT)
	    || options[1] != CILEN_DEFLATE
	    || DEFLATE_METHOD(options[2]) != DEFLATE_METHOD_VAL
	    || options[3] != DEFLATE_CHK_SEQUENCE)
		return NULL;
	w_size = DEFLATE_SIZE(options[2]);
	if (w_size < DEFLATE_MIN_SIZE || w_size > DEFLATE_MAX_SIZE)
		return NULL;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (state == NULL)
		return NULL;

	state->w_size         = w_size;
	state->strm.next_out  = NULL;
	state->strm.workspace = kmalloc(zlib_inflate_workspacesize(),
					GFP_KERNEL|__GFP_REPEAT);
	if (state->strm.workspace == NULL)
		goto out_free;

	if (zlib_inflateInit2(&state->strm, -w_size) != Z_OK)
		goto out_free;
	return (void *) state;

out_free:
	z_decomp_free(state);
	return NULL;
}