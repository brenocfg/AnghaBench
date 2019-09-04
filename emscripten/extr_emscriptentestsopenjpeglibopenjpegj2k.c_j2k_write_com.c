#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* cp; int /*<<< orphan*/ * cio; } ;
typedef  TYPE_2__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_4__ {char* comment; } ;

/* Variables and functions */
 int J2K_MS_COM ; 
 int /*<<< orphan*/  cio_seek (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,int) ; 
 int cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 
 unsigned int strlen (char*) ; 

__attribute__((used)) static void j2k_write_com(opj_j2k_t *j2k) {
	unsigned int i;
	int lenp, len;

	if(j2k->cp->comment) {
		opj_cio_t *cio = j2k->cio;
		char *comment = j2k->cp->comment;

		cio_write(cio, J2K_MS_COM, 2);
		lenp = cio_tell(cio);
		cio_skip(cio, 2);
		cio_write(cio, 1, 2);		/* General use (IS 8859-15:1999 (Latin) values) */
		for (i = 0; i < strlen(comment); i++) {
			cio_write(cio, comment[i], 1);
		}
		len = cio_tell(cio) - lenp;
		cio_seek(cio, lenp);
		cio_write(cio, len, 2);
		cio_seek(cio, lenp + len);
	}
}