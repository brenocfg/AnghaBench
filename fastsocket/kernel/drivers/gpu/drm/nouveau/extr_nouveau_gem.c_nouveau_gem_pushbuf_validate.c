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
typedef  int /*<<< orphan*/  uint64_t ;
struct validate_op {int /*<<< orphan*/  both_list; int /*<<< orphan*/  gart_list; int /*<<< orphan*/  vram_list; } ;
struct nouveau_cli {int dummy; } ;
struct nouveau_channel {int dummy; } ;
struct drm_nouveau_gem_pushbuf_bo {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_cli*,char*) ; 
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  validate_fini (struct validate_op*,int /*<<< orphan*/ *) ; 
 int validate_init (struct nouveau_channel*,struct drm_file*,struct drm_nouveau_gem_pushbuf_bo*,int,struct validate_op*) ; 
 int validate_list (struct nouveau_channel*,struct nouveau_cli*,int /*<<< orphan*/ *,struct drm_nouveau_gem_pushbuf_bo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nouveau_gem_pushbuf_validate(struct nouveau_channel *chan,
			     struct drm_file *file_priv,
			     struct drm_nouveau_gem_pushbuf_bo *pbbo,
			     uint64_t user_buffers, int nr_buffers,
			     struct validate_op *op, int *apply_relocs)
{
	struct nouveau_cli *cli = nouveau_cli(file_priv);
	int ret, relocs = 0;

	INIT_LIST_HEAD(&op->vram_list);
	INIT_LIST_HEAD(&op->gart_list);
	INIT_LIST_HEAD(&op->both_list);

	if (nr_buffers == 0)
		return 0;

	ret = validate_init(chan, file_priv, pbbo, nr_buffers, op);
	if (unlikely(ret)) {
		if (ret != -ERESTARTSYS)
			NV_ERROR(cli, "validate_init\n");
		return ret;
	}

	ret = validate_list(chan, cli, &op->vram_list, pbbo, user_buffers);
	if (unlikely(ret < 0)) {
		if (ret != -ERESTARTSYS)
			NV_ERROR(cli, "validate vram_list\n");
		validate_fini(op, NULL);
		return ret;
	}
	relocs += ret;

	ret = validate_list(chan, cli, &op->gart_list, pbbo, user_buffers);
	if (unlikely(ret < 0)) {
		if (ret != -ERESTARTSYS)
			NV_ERROR(cli, "validate gart_list\n");
		validate_fini(op, NULL);
		return ret;
	}
	relocs += ret;

	ret = validate_list(chan, cli, &op->both_list, pbbo, user_buffers);
	if (unlikely(ret < 0)) {
		if (ret != -ERESTARTSYS)
			NV_ERROR(cli, "validate both_list\n");
		validate_fini(op, NULL);
		return ret;
	}
	relocs += ret;

	*apply_relocs = relocs;
	return 0;
}