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
struct TYPE_3__ {int /*<<< orphan*/ * cio; } ;
typedef  TYPE_1__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int cio_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void j2k_read_com(opj_j2k_t *j2k) {
	int len;
	
	opj_cio_t *cio = j2k->cio;

	len = cio_read(cio, 2);
	cio_skip(cio, len - 2);  
}