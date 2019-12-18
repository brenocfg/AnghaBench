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
struct TYPE_3__ {int length; int ecd_length; char* ecd; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ ZIP ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ ecd_find_sig (char*,int,int*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logerror (char*,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int ecd_read(ZIP* zip) {
	char* buf;
	int buf_length = 1024; /* initial buffer length */

	while (1) {
		int offset;

		if (buf_length > zip->length)
			buf_length = zip->length;

		if (fseek(zip->fp, zip->length - buf_length, SEEK_SET) != 0) {
			return -1;
		}

		/* allocate buffer */
		buf = (char*)malloc( buf_length );
		if (!buf) {
			return -1;
		}

		if (fread( buf, buf_length, 1, zip->fp ) != 1) {
			free(buf);
			return -1;
		}

		if (ecd_find_sig(buf, buf_length, &offset)) {
			zip->ecd_length = buf_length - offset;

			zip->ecd = (char*)malloc( zip->ecd_length );
			if (!zip->ecd) {
				free(buf);
				return -1;
			}

			memcpy(zip->ecd, buf + offset, zip->ecd_length);

			free(buf);
			return 0;
		}

		free(buf);

		if (buf_length < zip->length) {
			/* double buffer */
			buf_length = 2*buf_length;

			logerror("Retry reading of zip ecd for %d bytes\n",buf_length);

		} else {
			return -1;
		}
	}
}