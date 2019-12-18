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
typedef  char uint8_t ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
 int INT_MAX ; 
 int SIZE_MAX ; 
 int av_file_map (char const*,char**,size_t*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  av_file_unmap (char*,size_t) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_isgraph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 char* av_malloc (int) ; 
 int* av_mallocz_array (int,int) ; 

__attribute__((used)) static int read_shape_from_file(int *cols, int *rows, int **values, const char *filename,
                                void *log_ctx)
{
    uint8_t *buf, *p, *pend;
    size_t size;
    int ret, i, j, w;

    if ((ret = av_file_map(filename, &buf, &size, 0, log_ctx)) < 0)
        return ret;

    /* prescan file to get the number of lines and the maximum width */
    w = 0;
    for (i = 0; i < size; i++) {
        if (buf[i] == '\n') {
            if (*rows == INT_MAX) {
                av_log(log_ctx, AV_LOG_ERROR, "Overflow on the number of rows in the file\n");
                ret = AVERROR_INVALIDDATA;
                goto end;
            }
            ++(*rows);
            *cols = FFMAX(*cols, w);
            w = 0;
        } else if (w == INT_MAX) {
            av_log(log_ctx, AV_LOG_ERROR, "Overflow on the number of columns in the file\n");
            return AVERROR_INVALIDDATA;
        }
        w++;
    }
    if (*rows > (SIZE_MAX / sizeof(int) / *cols)) {
        av_log(log_ctx, AV_LOG_ERROR, "File with size %dx%d is too big\n",
               *rows, *cols);
        ret = AVERROR_INVALIDDATA;
        goto end;
    }
    if (!(*values = av_mallocz_array(sizeof(int) * *rows, *cols))) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    /* fill *values */
    p    = buf;
    pend = buf + size-1;
    for (i = 0; i < *rows; i++) {
        for (j = 0;; j++) {
            if (p > pend || *p == '\n') {
                p++;
                break;
            } else
                (*values)[*cols*i + j] = !!av_isgraph(*(p++));
        }
    }

end:
    av_file_unmap(buf, size);

#ifdef DEBUG
    {
        char *line;
        if (!(line = av_malloc(*cols + 1)))
            return AVERROR(ENOMEM);
        for (i = 0; i < *rows; i++) {
            for (j = 0; j < *cols; j++)
                line[j] = (*values)[i * *cols + j] ? '@' : ' ';
            line[j] = 0;
            av_log(log_ctx, AV_LOG_DEBUG, "%3d: %s\n", i, line);
        }
        av_free(line);
    }
#endif

    return 0;
}