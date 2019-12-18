__attribute__((used)) static inline const void *_fdt_offset_ptr(const void *fdt, int offset)
{
	return (const char *)fdt + fdt_off_dt_struct(fdt) + offset;
}