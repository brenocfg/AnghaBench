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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  print_results (scalar_t__*,double*,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (char*,char*,int*,int*) ; 
 scalar_t__ ssd_plane (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 double ssim_plane (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char* argv[])
{
    FILE *f[2];
    uint8_t *buf[2], *plane[2][3];
    int *temp;
    uint64_t ssd[3] = {0,0,0};
    double ssim[3] = {0,0,0};
    int frame_size, w, h;
    int frames, seek;
    int i;

    if( argc<4 || 2 != sscanf(argv[3], "%dx%d", &w, &h) )
    {
        printf("tiny_ssim <file1.yuv> <file2.yuv> <width>x<height> [<seek>]\n");
        return -1;
    }

    f[0] = fopen(argv[1], "rb");
    f[1] = fopen(argv[2], "rb");
    sscanf(argv[3], "%dx%d", &w, &h);

    if (w<=0 || h<=0 || w*(int64_t)h >= INT_MAX/3 || 2LL*w+12 >= INT_MAX / sizeof(*temp)) {
        fprintf(stderr, "Dimensions are too large, or invalid\n");
        return -2;
    }

    frame_size = w*h*3LL/2;
    for( i=0; i<2; i++ )
    {
        buf[i] = malloc(frame_size);
        plane[i][0] = buf[i];
        plane[i][1] = plane[i][0] + w*h;
        plane[i][2] = plane[i][1] + w*h/4;
    }
    temp = malloc((2*w+12)*sizeof(*temp));
    seek = argc<5 ? 0 : atoi(argv[4]);
    fseek(f[seek<0], seek < 0 ? -seek : seek, SEEK_SET);

    for( frames=0;; frames++ )
    {
        uint64_t ssd_one[3];
        double ssim_one[3];
        if( fread(buf[0], frame_size, 1, f[0]) != 1) break;
        if( fread(buf[1], frame_size, 1, f[1]) != 1) break;
        for( i=0; i<3; i++ )
        {
            ssd_one[i]  = ssd_plane ( plane[0][i], plane[1][i], w*h>>2*!!i );
            ssim_one[i] = ssim_plane( plane[0][i], w>>!!i,
                                     plane[1][i], w>>!!i,
                                     w>>!!i, h>>!!i, temp, NULL );
            ssd[i] += ssd_one[i];
            ssim[i] += ssim_one[i];
        }

        printf("Frame %d | ", frames);
        print_results(ssd_one, ssim_one, 1, w, h);
        printf("                \r");
        fflush(stdout);
    }

    if( !frames ) return 0;

    printf("Total %d frames | ", frames);
    print_results(ssd, ssim, frames, w, h);
    printf("\n");

    return 0;
}