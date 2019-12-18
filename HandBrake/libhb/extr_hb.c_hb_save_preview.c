#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
struct TYPE_5__ {int max_plane; } ;
struct TYPE_7__ {TYPE_2__* plane; TYPE_1__ f; } ;
typedef  TYPE_3__ hb_buffer_t ;
struct TYPE_6__ {int stride; int width; int height; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_error (char*,...) ; 
 int /*<<< orphan*/ * hb_fopen (char*,char*) ; 
 int /*<<< orphan*/  hb_get_instance_id (int /*<<< orphan*/ *) ; 
 char* hb_get_temporary_filename (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strerror_r (int /*<<< orphan*/ ,char*,int) ; 

int hb_save_preview( hb_handle_t * h, int title, int preview, hb_buffer_t *buf )
{
    FILE * file;
    char * filename;
    char   reason[80];

    filename = hb_get_temporary_filename("%d_%d_%d", hb_get_instance_id(h),
                                         title, preview );

    file = hb_fopen(filename, "wb");
    if (file == NULL)
    {
        if (strerror_r(errno, reason, 79) != 0)
            strcpy(reason, "unknown -- strerror_r() failed");

        hb_error("hb_save_preview: Failed to open %s (reason: %s)",
                 filename, reason);
        free(filename);
        return -1;
    }

    int pp, hh;
    for( pp = 0; pp <= buf->f.max_plane; pp++ )
    {
        uint8_t *data = buf->plane[pp].data;
        int stride = buf->plane[pp].stride;
        int w = buf->plane[pp].width;
        int h = buf->plane[pp].height;

        for( hh = 0; hh < h; hh++ )
        {
            if (fwrite( data, w, 1, file ) < w)
            {
                if (ferror(file))
                {
                    if (strerror_r(errno, reason, 79) != 0)
                        strcpy(reason, "unknown -- strerror_r() failed");

                    hb_error( "hb_save_preview: Failed to write line %d to %s "
                              "(reason: %s). Preview will be incomplete.",
                              hh, filename, reason );
                    goto done;
                }
            }
            data += stride;
        }
    }

done:
    free(filename);
    fclose( file );

    return 0;
}