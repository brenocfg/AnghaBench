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
typedef  int /*<<< orphan*/  OPENMAX_JPEG_DECODER ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcm_host_init () ; 
 int /*<<< orphan*/  cleanup (int /*<<< orphan*/ *) ; 
 int decodeImage (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int setupOpenMaxJpegDecoder (int /*<<< orphan*/ **) ; 

int
main(int argc, char *argv[])
{
    OPENMAX_JPEG_DECODER *pDecoder;
    char           *sourceImage;
    size_t          imageSize;
    int             s;
    if (argc < 2) {
	printf("Usage: %s <filename>\n", argv[0]);
	return -1;
    }
    FILE           *fp = fopen(argv[1], "rb");
    if (!fp) {
	printf("File %s not found.\n", argv[1]);
    }
    fseek(fp, 0L, SEEK_END);
    imageSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    sourceImage = malloc(imageSize);
    assert(sourceImage != NULL);
    s = fread(sourceImage, 1, imageSize, fp);
    assert(s == imageSize);
    fclose(fp);
    bcm_host_init();
    s = setupOpenMaxJpegDecoder(&pDecoder);
    assert(s == 0);
    s = decodeImage(pDecoder, sourceImage, imageSize);
    assert(s == 0);
    cleanup(pDecoder);
    free(sourceImage);
    return 0;
}