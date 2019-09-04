#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  j2k_codestream_offset; int /*<<< orphan*/  j2k_codestream_length; } ;
typedef  TYPE_1__ opj_jp2_t ;
typedef  int /*<<< orphan*/  opj_jp2_color_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int /*<<< orphan*/  jp2_read_ftyp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jp2_read_jp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jp2_read_jp2c (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jp2_read_jp2h (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool jp2_read_struct(opj_jp2_t *jp2, opj_cio_t *cio,
	opj_jp2_color_t *color) {
	if (!jp2_read_jp(jp2, cio))
		return false;
	if (!jp2_read_ftyp(jp2, cio))
		return false;
	if (!jp2_read_jp2h(jp2, cio, color))
		return false;
	if (!jp2_read_jp2c(jp2, cio, &jp2->j2k_codestream_length, &jp2->j2k_codestream_offset))
		return false;
	
	return true;
}