__attribute__((used)) static void address() {
    struct tag { int a; struct { int b; } y; } x = { 6, 7 };
    int *p1 = &x.a;
    int *p2 = &x.y.b;
    expect(6, *p1);
    expect(7, *p2);
    expect(6, *&x.a);
    expect(7, *&x.y.b);

    struct tag *xp = &x;
    int *p3 = &xp->a;
    int *p4 = &xp->y.b;
    expect(6, *p3);
    expect(7, *p4);
    expect(6, *&xp->a);
    expect(7, *&xp->y.b);
}