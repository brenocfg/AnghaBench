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
struct sg_map_node {int /*<<< orphan*/  sg_dmamap; int /*<<< orphan*/  sg_vaddr; } ;
struct scb_data {int init_level; struct sg_map_node* scbarray; int /*<<< orphan*/  hscb_dmat; int /*<<< orphan*/  hscb_dmamap; int /*<<< orphan*/  hscbs; int /*<<< orphan*/  sense_dmat; int /*<<< orphan*/  sense_dmamap; int /*<<< orphan*/  sense; int /*<<< orphan*/  sg_dmat; int /*<<< orphan*/  sg_maps; } ;
struct ahc_softc {struct scb_data* scb_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 struct sg_map_node* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_dma_tag_destroy (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_dmamap_destroy (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_dmamap_unload (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_dmamem_free (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sg_map_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 

__attribute__((used)) static void
ahc_fini_scbdata(struct ahc_softc *ahc)
{
	struct scb_data *scb_data;

	scb_data = ahc->scb_data;
	if (scb_data == NULL)
		return;

	switch (scb_data->init_level) {
	default:
	case 7:
	{
		struct sg_map_node *sg_map;

		while ((sg_map = SLIST_FIRST(&scb_data->sg_maps))!= NULL) {
			SLIST_REMOVE_HEAD(&scb_data->sg_maps, links);
			ahc_dmamap_unload(ahc, scb_data->sg_dmat,
					  sg_map->sg_dmamap);
			ahc_dmamem_free(ahc, scb_data->sg_dmat,
					sg_map->sg_vaddr,
					sg_map->sg_dmamap);
			free(sg_map, M_DEVBUF);
		}
		ahc_dma_tag_destroy(ahc, scb_data->sg_dmat);
	}
	case 6:
		ahc_dmamap_unload(ahc, scb_data->sense_dmat,
				  scb_data->sense_dmamap);
	case 5:
		ahc_dmamem_free(ahc, scb_data->sense_dmat, scb_data->sense,
				scb_data->sense_dmamap);
		ahc_dmamap_destroy(ahc, scb_data->sense_dmat,
				   scb_data->sense_dmamap);
	case 4:
		ahc_dma_tag_destroy(ahc, scb_data->sense_dmat);
	case 3:
		ahc_dmamap_unload(ahc, scb_data->hscb_dmat,
				  scb_data->hscb_dmamap);
	case 2:
		ahc_dmamem_free(ahc, scb_data->hscb_dmat, scb_data->hscbs,
				scb_data->hscb_dmamap);
		ahc_dmamap_destroy(ahc, scb_data->hscb_dmat,
				   scb_data->hscb_dmamap);
	case 1:
		ahc_dma_tag_destroy(ahc, scb_data->hscb_dmat);
		break;
	case 0:
		break;
	}
	if (scb_data->scbarray != NULL)
		free(scb_data->scbarray, M_DEVBUF);
}