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
typedef  int /*<<< orphan*/  uLongf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MEM_LIMIT ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  Z_BEST_COMPRESSION ; 
 int Z_BUF_ERROR ; 
 int Z_OK ; 
 scalar_t__ atoi (char*) ; 
 int compress2 (void*,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (void*,int,int,int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 void* realloc (void*,int) ; 
 int uncompress (void*,int /*<<< orphan*/ *,void*,int) ; 

int main(int argc, char *argv[])
{
	void *pi, *po = NULL;
	FILE *fi, *fo;
	int ret, si, so;

	if (argc != 4)
	{
		printf("usage: %s <0|1> <infile> <outfile>\n", argv[0]);
		return 1;
	}

	fi = fopen(argv[2], "rb");
	if (fi == NULL) return 2;

	fseek(fi, 0, SEEK_END);
	si = ftell(fi);
	fseek(fi, 0, SEEK_SET);
	pi = malloc(si);
	if (pi == NULL) return 3;
	fread(pi, 1, si, fi);
	fclose(fi);

	if (atoi(argv[1]))
	{
		// decompress
		so = si;
		do
		{
			so *= 16;
			if (so > MEM_LIMIT) return 4;
			po = realloc(po, so);
			if (po == NULL) return 5;
			ret = uncompress(po, (uLongf *) &so, pi, si);
		}
		while (ret == Z_BUF_ERROR);
	}
	else
	{
		// compress
		so = si + 1024;
		po = malloc(so);
		if (po == NULL) return 5;
		ret = compress2(po, (uLongf *) &so, pi, si, Z_BEST_COMPRESSION);
	}

	if (ret == Z_OK)
	{
		fo = fopen(argv[3], "wb");
		if (fo == NULL) return 6;
		fwrite(po, 1, so, fo);
		fclose(fo);
	}

	printf("result %i, size %i -> %i\n", ret, si, so);

	return ret;
}