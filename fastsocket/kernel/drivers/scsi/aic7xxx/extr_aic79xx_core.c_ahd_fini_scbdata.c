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
struct scb_data {int init_level; int /*<<< orphan*/  hscb_dmat; int /*<<< orphan*/  hscb_maps; int /*<<< orphan*/  sg_dmat; int /*<<< orphan*/  sg_maps; int /*<<< orphan*/  sense_dmat; int /*<<< orphan*/  sense_maps; } ;
struct map_node {int /*<<< orphan*/  dmamap; int /*<<< orphan*/  vaddr; } ;
struct ahd_softc {struct scb_data scb_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 struct map_node* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_dma_tag_destroy (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_dmamap_unload (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_dmamem_free (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct map_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 

__attribute__((used)) static void
ahd_fini_scbdata(struct ahd_softc *ahd)
{
	struct scb_data *scb_data;

	scb_data = &ahd->scb_data;
	if (scb_data == NULL)
		return;

	switch (scb_data->init_level) {
	default:
	case 7:
	{
		struct map_node *sns_map;

		while ((sns_map = SLIST_FIRST(&scb_data->sense_maps)) != NULL) {
			SLIST_REMOVE_HEAD(&scb_data->sense_maps, links);
			ahd_dmamap_unload(ahd, scb_data->sense_dmat,
					  sns_map->dmamap);
			ahd_dmamem_free(ahd, scb_data->sense_dmat,
					sns_map->vaddr, sns_map->dmamap);
			free(sns_map, M_DEVBUF);
		}
		ahd_dma_tag_destroy(ahd, scb_data->sense_dmat);
		/* FALLTHROUGH */
	}
	case 6:
	{
		struct map_node *sg_map;

		while ((sg_map = SLIST_FIRST(&scb_data->sg_maps)) != NULL) {
			SLIST_REMOVE_HEAD(&scb_data->sg_maps, links);
			ahd_dmamap_unload(ahd, scb_data->sg_dmat,
					  sg_map->dmamap);
			ahd_dmamem_free(ahd, scb_data->sg_dmat,
					sg_map->vaddr, sg_map->dmamap);
			free(sg_map, M_DEVBUF);
		}
		ahd_dma_tag_destroy(ahd, scb_data->sg_dmat);
		/* FALLTHROUGH */
	}
	case 5:
	{
		struct map_node *hscb_map;

		while ((hscb_map = SLIST_FIRST(&scb_data->hscb_maps)) != NULL) {
			SLIST_REMOVE_HEAD(&scb_data->hscb_maps, links);
			ahd_dmamap_unload(ahd, scb_data->hscb_dmat,
					  hscb_map->dmamap);
			ahd_dmamem_free(ahd, scb_data->hscb_dmat,
					hscb_map->vaddr, hscb_map->dmamap);
			free(hscb_map, M_DEVBUF);
		}
		ahd_dma_tag_destroy(ahd, scb_data->hscb_dmat);
		/* FALLTHROUGH */
	}
	case 4:
	case 3:
	case 2:
	case 1:
	case 0:
		break;
	}
}