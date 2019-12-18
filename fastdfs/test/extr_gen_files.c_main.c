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
struct TYPE_2__ {char* filename; int bytes; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFF_SIZE ; 
 int FILE_TYPE_COUNT ; 
 double RAND_MAX ; 
 int /*<<< orphan*/  SRAND_SEED ; 
 char* STRERROR (int) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 TYPE_1__* files ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 

int main()
{
#define BUFF_SIZE  (1 * 1024)
	int i;
	int k;
	int loop;
	FILE *fp;
	unsigned char buff[BUFF_SIZE];
	unsigned char *p;
	unsigned char *pEnd;

	srand(SRAND_SEED);
	pEnd = buff + BUFF_SIZE;
	for (i=0; i<FILE_TYPE_COUNT; i++)
	{
		fp = fopen(files[i].filename, "wb");
		if (fp == NULL)
		{
			printf("open file %s fail, errno: %d, error info: %s\n", 
				files[i].filename, errno, STRERROR(errno));
			return 1;
		}

		loop = files[i].bytes / BUFF_SIZE;
		for (k=0; k<loop-1; k++)
		{
			for (p=buff; p<pEnd; p++)
			{
				*p = (int)(255 * ((double)rand() / RAND_MAX));
			}

			if (fwrite(buff, BUFF_SIZE, 1, fp) != 1)
			{
				printf("write file %s fail, errno: %d, error info: %s\n", 
					files[i].filename, errno, STRERROR(errno));
		        fclose(fp);
				return 1;
			}
		}

		memset(buff, 0xFF, BUFF_SIZE);
		if (fwrite(buff, BUFF_SIZE, 1, fp) != 1)
		{
			printf("write file %s fail, errno: %d, error info: %s\n", 
				files[i].filename, errno, STRERROR(errno));
		    fclose(fp);
			return 1;
		}

		fclose(fp);
	}

	printf("done.\n");

	return 0;
}