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
struct stat {int st_size; } ;
struct sec_add {int size; int* content; int /*<<< orphan*/ * name; } ;
struct elfcopy {scalar_t__ oed; int /*<<< orphan*/  flags; int /*<<< orphan*/  v_sadd; int /*<<< orphan*/ * debuglink; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ELFDATA2LSB ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SEC_ADD ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct sec_add*,int /*<<< orphan*/ ) ; 
 char* basename (int /*<<< orphan*/ *) ; 
 int calc_crc32 (char*,int,int) ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (int) ; 
 int roundup (scalar_t__,int) ; 
 int /*<<< orphan*/  sadd_list ; 
 int stat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int*,char*,scalar_t__) ; 

__attribute__((used)) static void
add_gnu_debuglink(struct elfcopy *ecp)
{
	struct sec_add	*sa;
	struct stat	 sb;
	FILE		*fp;
	char		*fnbase, *buf;
	int		 crc_off;
	int		 crc;

	if (ecp->debuglink == NULL)
		return;

	/* Read debug file content. */
	if ((sa = malloc(sizeof(*sa))) == NULL)
		err(EXIT_FAILURE, "malloc failed");
	if ((sa->name = strdup(".gnu_debuglink")) == NULL)
		err(EXIT_FAILURE, "strdup failed");
	if (stat(ecp->debuglink, &sb) == -1)
		err(EXIT_FAILURE, "stat failed");
	if (sb.st_size == 0)
		errx(EXIT_FAILURE, "empty debug link target %s",
		    ecp->debuglink);
	if ((buf = malloc(sb.st_size)) == NULL)
		err(EXIT_FAILURE, "malloc failed");
	if ((fp = fopen(ecp->debuglink, "r")) == NULL)
		err(EXIT_FAILURE, "can not open %s", ecp->debuglink);
	if (fread(buf, 1, sb.st_size, fp) == 0 ||
	    ferror(fp))
		err(EXIT_FAILURE, "fread failed");
	fclose(fp);

	/* Calculate crc checksum.  */
	crc = calc_crc32(buf, sb.st_size, 0xFFFFFFFF);
	free(buf);

	/* Calculate section size and the offset to store crc checksum. */
	if ((fnbase = basename(ecp->debuglink)) == NULL)
		err(EXIT_FAILURE, "basename failed");
	crc_off = roundup(strlen(fnbase) + 1, 4);
	sa->size = crc_off + 4;

	/* Section content. */
	if ((sa->content = calloc(1, sa->size)) == NULL)
		err(EXIT_FAILURE, "malloc failed");
	strncpy(sa->content, fnbase, strlen(fnbase));
	if (ecp->oed == ELFDATA2LSB) {
		sa->content[crc_off] = crc & 0xFF;
		sa->content[crc_off + 1] = (crc >> 8) & 0xFF;
		sa->content[crc_off + 2] = (crc >> 16) & 0xFF;
		sa->content[crc_off + 3] = crc >> 24;
	} else {
		sa->content[crc_off] = crc >> 24;
		sa->content[crc_off + 1] = (crc >> 16) & 0xFF;
		sa->content[crc_off + 2] = (crc >> 8) & 0xFF;
		sa->content[crc_off + 3] = crc & 0xFF;
	}

	STAILQ_INSERT_TAIL(&ecp->v_sadd, sa, sadd_list);
	ecp->flags |= SEC_ADD;
}