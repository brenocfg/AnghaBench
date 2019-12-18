__attribute__((used)) static inline unsigned in_le32(const volatile unsigned *addr)
{
	unsigned ret;

	__asm__ __volatile__("lwbrx %0,0,%1; twi 0,%0,0; isync"
			     : "=r" (ret) : "r" (addr), "m" (*addr));
	return ret;
}