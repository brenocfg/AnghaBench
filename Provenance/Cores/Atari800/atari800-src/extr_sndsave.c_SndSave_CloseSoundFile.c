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
 scalar_t__ EOF ; 
 int FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int TRUE ; 
 int byteswritten ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ putc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sndoutput ; 
 int /*<<< orphan*/  write32 (int) ; 

int SndSave_CloseSoundFile(void)
{
	int bSuccess = TRUE;
	char aligned = 0;

	if (sndoutput != NULL) {
		/* A RIFF file's chunks must be word-aligned. So let's align. */
		if (byteswritten & 1) {
			if (putc(0, sndoutput) == EOF)
				bSuccess = FALSE;
			else
				aligned = 1;
		}

		if (bSuccess) {
			/* Sound file is finished, so modify header and close it. */
			if (fseek(sndoutput, 4, SEEK_SET) != 0)	/* Seek past RIFF */
				bSuccess = FALSE;
			else {
				/* RIFF header's size field must equal the size of all chunks
				 * with alignment, so the alignment byte is added.
				 */
				write32(byteswritten + 36 + aligned);
				if (fseek(sndoutput, 40, SEEK_SET) != 0)
					bSuccess = FALSE;
				else {
					/* But in the "data" chunk size field, the alignment byte
					 * should be ignored. */
					write32(byteswritten);
				}
			}
		}
		fclose(sndoutput);
		sndoutput = NULL;
	}

	return bSuccess;
}