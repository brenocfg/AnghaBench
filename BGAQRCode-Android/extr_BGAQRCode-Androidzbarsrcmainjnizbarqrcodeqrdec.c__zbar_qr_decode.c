#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ zbar_image_t ;
typedef  int /*<<< orphan*/  zbar_image_scanner_t ;
struct TYPE_16__ {TYPE_1__* finder_lines; } ;
typedef  TYPE_3__ qr_reader ;
typedef  void qr_finder_edge_pt ;
typedef  void qr_finder_center ;
struct TYPE_17__ {scalar_t__ nqrdata; } ;
typedef  TYPE_4__ qr_code_data_list ;
struct TYPE_14__ {int nlines; } ;

/* Variables and functions */
 int QR_FINDER_SUBPREC ; 
 int /*<<< orphan*/  free (void*) ; 
 void* qr_binarize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qr_code_data_list_clear (TYPE_4__*) ; 
 int qr_code_data_list_extract_text (TYPE_4__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  qr_code_data_list_init (TYPE_4__*) ; 
 int qr_finder_centers_locate (void**,void**,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qr_reader_match_centers (TYPE_3__*,TYPE_4__*,void*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qr_svg_centers (void*,int) ; 
 int /*<<< orphan*/  svg_group_end () ; 
 int /*<<< orphan*/  svg_group_start (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zprintf (int,char*,int,int,int) ; 

int _zbar_qr_decode (qr_reader *reader,
                     zbar_image_scanner_t *iscn,
                     zbar_image_t *img)
{
    int nqrdata = 0, ncenters;
    qr_finder_edge_pt *edge_pts = NULL;
    qr_finder_center *centers = NULL;

    if(reader->finder_lines[0].nlines < 9 ||
       reader->finder_lines[1].nlines < 9)
        return(0);

    svg_group_start("finder", 0, 1. / (1 << QR_FINDER_SUBPREC), 0, 0, 0);

    ncenters = qr_finder_centers_locate(&centers, &edge_pts, reader, 0, 0);

    zprintf(14, "%dx%d finders, %d centers:\n",
            reader->finder_lines[0].nlines,
            reader->finder_lines[1].nlines,
            ncenters);
    qr_svg_centers(centers, ncenters);

    if(ncenters >= 3) {
        void *bin = qr_binarize(img->data, img->width, img->height);

        qr_code_data_list qrlist;
        qr_code_data_list_init(&qrlist);

        qr_reader_match_centers(reader, &qrlist, centers, ncenters,
                                bin, img->width, img->height);

        if(qrlist.nqrdata > 0)
            nqrdata = qr_code_data_list_extract_text(&qrlist, iscn, img);

        qr_code_data_list_clear(&qrlist);
        free(bin);
    }
    svg_group_end();

    if(centers)
        free(centers);
    if(edge_pts)
        free(edge_pts);
    return(nqrdata);
}