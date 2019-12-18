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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  URL_FILE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FGETSFILE ; 
 int /*<<< orphan*/  FREADFILE ; 
 int /*<<< orphan*/  REWINDFILE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  url_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  url_feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  url_fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * url_fopen (char const*,char*) ; 
 size_t url_fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  url_rewind (int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[])
{
  URL_FILE *handle;
  FILE *outf;

  size_t nread;
  char buffer[256];
  const char *url;

  if(argc < 2)
    url = "http://192.168.7.3/testfile";/* default to testurl */
  else
    url = argv[1];/* use passed url */

  /* copy from url line by line with fgets */
  outf = fopen(FGETSFILE, "wb+");
  if(!outf) {
    perror("couldn't open fgets output file\n");
    return 1;
  }

  handle = url_fopen(url, "r");
  if(!handle) {
    printf("couldn't url_fopen() %s\n", url);
    fclose(outf);
    return 2;
  }

  while(!url_feof(handle)) {
    url_fgets(buffer, sizeof(buffer), handle);
    fwrite(buffer, 1, strlen(buffer), outf);
  }

  url_fclose(handle);

  fclose(outf);


  /* Copy from url with fread */
  outf = fopen(FREADFILE, "wb+");
  if(!outf) {
    perror("couldn't open fread output file\n");
    return 1;
  }

  handle = url_fopen("testfile", "r");
  if(!handle) {
    printf("couldn't url_fopen() testfile\n");
    fclose(outf);
    return 2;
  }

  do {
    nread = url_fread(buffer, 1, sizeof(buffer), handle);
    fwrite(buffer, 1, nread, outf);
  } while(nread);

  url_fclose(handle);

  fclose(outf);


  /* Test rewind */
  outf = fopen(REWINDFILE, "wb+");
  if(!outf) {
    perror("couldn't open fread output file\n");
    return 1;
  }

  handle = url_fopen("testfile", "r");
  if(!handle) {
    printf("couldn't url_fopen() testfile\n");
    fclose(outf);
    return 2;
  }

  nread = url_fread(buffer, 1, sizeof(buffer), handle);
  fwrite(buffer, 1, nread, outf);
  url_rewind(handle);

  buffer[0]='\n';
  fwrite(buffer, 1, 1, outf);

  nread = url_fread(buffer, 1, sizeof(buffer), handle);
  fwrite(buffer, 1, nread, outf);

  url_fclose(handle);

  fclose(outf);

  return 0;/* all done */
}